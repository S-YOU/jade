## slim-jade

When you use jade for client side (like with angular),
you don't always need dynamic features or fancy features that jade provided.
This is where slim-jade comes in. If you use gulp, you can use gulp-slim-jade.

installation:
- for python `sudo pip install jade`
- for nodejs `npm install slim-jade`

performance:
500~1500 times faster than jadejs/jade(1.11.0) in my project around 175 jade files (~250kB)
```
read: 29.708ms
slim-jade: 2.348ms
jadejs/jade: 3190.300ms
```

supported syntax:
- #id
- .a.b.c
- tag
- above3(a,b="a",c=1)
- above4 text
- | text
- = 'text'
- `//` jade comments and `<!-- html -->` comments are ignored
- experimental '.' block support, Eg. script.
- `<` one liner html tags will keep as is
- extra: `///` will convert to html comments `<!--abcd-->`

unsupported syntax:
- does not support stacked tags a: b: c. if program encounter ':', the whole program will exit.

limitations:
- only support tab indent, and it is upto 16 levels
- tag name must be less than 32 chars
- output html must be less than 100k
- class attr value cannot be more than 256 chars
- must be valid jade, with only mentioned features

if you break the limit, it will segfault or may crash your computer. Use at your own risk.
