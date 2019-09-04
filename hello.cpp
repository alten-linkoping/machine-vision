// hello.cpp
#include <node.h>

using namespace v8;

void Method(const FunctionCallbackInfo<Value>& args) {
      Isolate* isolate = args.GetIsolate();

    // create a new object on the v8 heap (json object)
    Local<Object> obj = Object::New(isolate);

    // set field "hello" with string "Why hello there." in that object
    obj->Set(String::NewFromUtf8(isolate, "image1"), String::NewFromUtf8(isolate, "{coordinates1}"));
obj->Set(String::NewFromUtf8(isolate, "image2"), String::NewFromUtf8(isolate, "{coordinates2}"));
//obj->Set(String::NewFromUtf8(isolate, "hello"), String::NewFromUtf8(isolate, "{Why hello there xd}"));

    // return object
    args.GetReturnValue().Set(obj);
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "hello", Method);
}

NODE_MODULE(hello_addon, init)

