#include <stdio.h>
#include <json-c/json.h>
#include <json-c/json_object.h>
#include <stdlib.h>

int main()
{
#if 0
    {"way" : 1, "name" : "zhangsan", "passwd" : "abc123"}
#endif

    /* 新建json对象 */
    struct json_object *jsonObj = json_object_new_object();
    json_object_object_add(jsonObj, "sites", json_object_new_string("www.runoob.com"));
    json_object_object_add(jsonObj, "sites", json_object_new_string("n.runoob.com"));

    struct json_object *jsonObj2 = json_object_new_object();
    json_object_object_add(jsonObj2, "shopping", json_object_new_string("jingdong"));
    json_object_object_add(jsonObj2, "shopping", json_object_new_string("pingduoduo"));
    json_object_object_add(jsonObj2, "shopping", json_object_new_string("Taobao"));

    struct json_object *jsonObj3 = json_object_new_object();
    
    json_object_object_add(jsonObj3, "name", json_object_new_string("runoob"));
    json_object_object_add(jsonObj3, "alexa", json_object_new_int("10000"));
    json_object_object_add(jsonObj3, "shopping", jsonObj2);
    json_object_object_add(jsonObj3, "sites", jsonObj);
    
    const char * str = json_object_to_json_string(jsonObj3);
    printf("%s\n", str);
    json_object_put(jsonObj3);
    return 0;
}