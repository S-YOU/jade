#include <node.h>
#include <nan.h>
#include "src/jade.h"

namespace {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::String;
using v8::Value;
using v8::Handle;

void compileFn(const Nan::FunctionCallbackInfo<v8::Value>& args) {
	String::Utf8Value str(args[0]->ToObject());
	unsigned char *src = (unsigned char*)*str;
	unsigned len;
	unsigned char *dst;

	const char* err_msg = nullptr;
	if (args.Length() != 1) {
		err_msg = "Wrong number of arguments: expected 1";
		goto err;
	}
	if (!args[0]->IsString()) {
		err_msg = "Input must be String";
		goto err;
	}

	dst = jade_compile(src, &len);

	return args.GetReturnValue().Set(Nan::New<String>((char *)dst, len).ToLocalChecked());

err:
	Nan::ThrowError(Nan::New<String>(err_msg).ToLocalChecked());
}


NAN_MODULE_INIT(Init) {

	v8::Local<v8::Function> _compileFn = Nan::GetFunction(
		Nan::New<v8::FunctionTemplate>(compileFn)).ToLocalChecked();

	Nan::Set(target, Nan::New("compile").ToLocalChecked(), _compileFn);
}

NODE_MODULE(addon, Init)

}
