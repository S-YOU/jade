{
	"targets": [{
		"target_name": "slim-jade",
		"sources": [
			"node.cc",
			"src/jade.c",
			"src/jade.h"
		],
		"include_dirs": [
			"<!(node -e \"require('nan')\")"
		],
		"cflags" : ["-std=c99", "-O3", "-fPIC", "-DNDEBUG", "-Wall"],
		"cflags_cc": ["-std=c99", "-O3", "-fPIC", "-DNDEBUG", "-Wall"],
		"conditions": [
		]
	}]
}
