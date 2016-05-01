#include "jade.h"

const char VALID_WORD[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
const char VALID_ATTR_DELIM[] = {0,0,0,0,0,0,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
const char VALID_ATTR_COPY[] = {0,1,1,1,1,1,1,1,1,0,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

#define SKIP_SPACES while (*s == ' ') s++;

#define COUNT_LVL \
	prevLvl = lvl, lvl = 0;\
	while (*s == 9) { lvl++, s++; }\
	SKIP_SPACES //extra spaces

#define COPY_WORD(D) \
	while (VALID_WORD[*s]) { *D++ = *s++; }

#define COPY_WORD_EX(D) \
	while (VALID_WORD[*s]) { *d++ = *D++ = *s++; }

#define HTML_ENCODE(d) \
	if (*s == '&') { *(uint32_t*)d = 0x706d6126, d += 4, *d++ = ';'; \
	} else if (*s == '"') { *(uint32_t*)d = 0x6f757126, d += 4, *(uint16_t*)d = 0x3b74, d += 2; \
	} else if (*s == '>') { *(uint32_t*)d = 0x3b746726, d += 4; \
	} else if (*s == '<') { *(uint32_t*)d = 0x3b746c26, d += 4; \
	} else { *d++ = *s; }

#define COPY_ATTR_VALUE(d) \
	if (*s == 34 || *s == 39) {\
		ch = *s++;\
		while (*s != ch) { \
			if (*s == '\\') { *d++ = *s++; } \
			HTML_ENCODE(d); \
			s++;\
		}\
		s++;\
	} else {\
		while(VALID_ATTR_COPY[*s]) { *d++ = *s++; }\
	}

#define COPY_UNQUOTED_VALUE \
	ch = *s++;\
	while (*s != ch) { if (*s == '\\') s++; HTML_ENCODE(d); s++; }\
	s++;

#define COPY_BLOCK \
	s += 2, i = 0;\
	while (s[i] == 9) i++;\
	while (i > lvl) {\
		s = s + i;\
		while (*s != '\n') *d++ = *s++;\
		s++, i = 0;\
		while (s[i] == 9) i++;\
		if (i <= lvl) {s--; break;}\
		*d++ = ' ';\
	}

#define DEFAULT_DIV \
	if (!tagsLen[lvl]) {\
		t = tags[lvl];\
		*(uint32_t*)d = 0x7669643c, d += 4;\
		*(uint32_t*)t = 0x766964;\
		tagsLen[lvl] = 3;\
	}

#define WRITE_CLS \
	if (c != cls) {\
		*(uint64_t*)d = 0x223d7373616c6320, d += 8;\
		memcpy(d, cls, c - cls);\
		d += c - cls;\
		*d++ = '"';\
	}

#define WRITE_INNER \
	while (*s && *s != '\n') { *d++ = *s++; }\

#define WRITE_CLOSE_TAG(I) \
	if ((tLen = tagsLen[I])) {\
		t = tags[I];\
		if ((tLen == 3 && (*(uint32_t*)t & 0x676d69) == 0x676d69) || \
			(tLen == 5 && *(uint32_t*)t == 0x75706e69 && t[4] == 't') || \
			(tLen == 2 && t[1] == 'r' && (t[0] == 'h' || t[0] == 'b'))\
		) {\
		} else {\
			*(uint16_t*)d = 0x2f3c, d += 2;\
			memcpy(d, tags[I], tagsLen[I]);\
			d += tagsLen[I];\
			*d++ = '>';\
		}\
		tagsLen[I] = *tags[I] = 0;\
	}

//global variables
unsigned char buffer[100000]; //output buffer
unsigned char cls[256]; //length of cls names
unsigned char tags[16][32]; //16 levels, 32 chars
unsigned tagsLen[16];

unsigned char* jade_compile(unsigned char *src, unsigned *len) {
	memset(&cls, 0, 256);
	memset(&tags, 0, 16 * 32);
	memset(&tagsLen, 0, 16);

	int lvl = 0, prevLvl = lvl, i = 0;
	unsigned tLen = 0;
	unsigned char *s = src, *d = buffer, *c = cls, *t, attrStarted = 0, openTag = 0, commentedLvl = 0, ch = 0;

	while (*s) {
		//drop windows cr
		if (*s == '\r') {
			s++;
		} else if (*s == '\n') {
			//ignore continuous blank lines (without indent)
			while (*s == '\n') s++;
			c = cls;
			COUNT_LVL
			//if commented, drop it
			if (commentedLvl) {
				if (lvl > commentedLvl) {
					while (*s != '\n') s++;
					continue;
				} else {
					commentedLvl = 0;
				}
			}
			//write close tags
			if (lvl <= prevLvl) {
				for (i = prevLvl; i >= lvl; i--) {
					WRITE_CLOSE_TAG(i)
				}
			}
		} else if (*s == '.') {
			//set div if none set
			if (!tagsLen[lvl]) {
				DEFAULT_DIV
			}
		cls:
			s++;
			if (c != cls) *c++ = ' ';
			COPY_WORD(c)
			if (*(uint16_t*)s == 0xa2e) {
				WRITE_CLS
				*d++ = '>';
				COPY_BLOCK
				openTag = 0;
			//more classes
			} else if (*s == '.') {
				goto cls;
			//write class
			} else if (*s == '\n') {
				WRITE_CLS
				*d++ = '>';
				openTag = 0;
			//write text
			} else if (*s == ' ') {
				WRITE_CLS
				*d++ = '>';
				openTag = 0;
				s++;
				WRITE_INNER
			} else {
				openTag = 1;
			}
		} else if (*s == '#') {
			//set div if none set
			if (!tagsLen[lvl]) {
				DEFAULT_DIV
			}
			s++;
			*d++ = ' ', *(uint32_t*)d = 0x223d6469, d += 4;
			COPY_WORD(d);
			*d++ = '"';
			//write class
			if (*s == '\n') {
				WRITE_CLS
				*d++ = '>';
				openTag = 0;
			//write text
			} else if (*s == ' ') {
				WRITE_CLS
				*d++ = '>';
				openTag = 0;
				s++;
				WRITE_INNER
			} else if (*(uint16_t*)s == 0xa2e) {
				WRITE_CLS
				*d++ = '>';
				openTag = 0;
				COPY_BLOCK
			} else {
				openTag = 1;
			}
		} else if (*s == '(') {
			attrStarted = 1;
			s++;
			while(VALID_ATTR_DELIM[*s]) s++; //ignore white spaces
		} else if (*s == ')') {
			attrStarted = 0;
			WRITE_CLS
			*d++ = '>';
			openTag = 0;
			s++;
			//write text
			if (*s == ' ') {
				s++; WRITE_INNER
			} else if (*(uint16_t*)s == 0xa2e) {
				COPY_BLOCK
			}
		} else if (*s == '=') {
			s += 2;
			SKIP_SPACES
			COPY_UNQUOTED_VALUE
		} else if (*s == '|') {
			s += 2;
			WRITE_INNER
		} else if (*(uint16_t*)s == 0x2f2f) {
			if (s[2] == 0x2f) {
				*(uint32_t*)d = 0x2d2d213c, d += 4, s += 3;
				while (*s && *s != '\n') *d++ = *s++;
				*(uint32_t*)d = 0x3e2d2d, d += 3;
			} else {
				while (*s && *s != '\n') s++;
			}
			commentedLvl = lvl;
		} else if (*(uint16_t*)s == 0x213c) {
			while ((*(uint32_t*)s & 0x3e2d2d) != 0x3e2d2d) {
				s++;
			}
			s += 3;
		} else if (*s == '<') {
			while (*s != '\n') *d++ = *s++;
		} else if (*s == ':') {
			printf("ERROR: stacked tags unsupported: %s\n", s);
			exit(1);
			s += 2;
		} else if (VALID_WORD[*s]) {
			if (attrStarted) {//attr
			attr:
				if (*(uint32_t*)s == 0x73616c63 && s[4] == 's' && !VALID_WORD[s[5]]) {
					s += 5;
					SKIP_SPACES //after attr name
					if (*s == '=') {
						s++;
						SKIP_SPACES
						if (c != cls) *c++ = ' ';
						COPY_ATTR_VALUE(c)
					}
				} else {
					*d++ = ' ';
					COPY_WORD(d)
					SKIP_SPACES //after attr name
					if (*s == '=') {
						*d++ = *s++;
						SKIP_SPACES //before attr value
						*d++ = '"';
						COPY_ATTR_VALUE(d)
						*d++ = '"';
					}
				}
				SKIP_SPACES //after attr val
				//if next attr go do again
				if (*s == ',' || *s == '\n') { while(VALID_ATTR_DELIM[*s]) s++; goto attr; }
			} else { //tag
				if (openTag) {
					*d++ = '>';
				}
				t = tags[lvl];
				*d++ = '<';
				COPY_WORD_EX(t)
				tagsLen[lvl] = t - tags[lvl];
				*t++ = 0;
				if (*s == ' ') {
					*d++ = '>'; s++;
					WRITE_INNER
				} else if (*s == '\n') {
					*d++ = '>';
				} else if (*(uint16_t*)s == 0xa2e) {
					*d++ = '>';
					COPY_BLOCK
				} else {
					openTag = 1;
				}
			}
		} else {
			printf("%c: unknown", *s);
			s++;
		}
	}

	WRITE_CLS

	if (openTag) {
		*d++ = '>';
	}

 	//printf("lvl: %d, prevLvl: %d\n", lvl, prevLvl);
	for (i = lvl; i >= 0; i--) {
		WRITE_CLOSE_TAG(i)
	}
	*d = 0;
	*len = d - buffer;

	return buffer;
}
