//
// Created by Administrator on 2019/3/30 0030.
//
#include <iostream>
#include "ejson.h"
#include "tinytemplate.h"

using namespace TinyTemplate;
using namespace EasyJson;
using namespace std;

int main() {
    HtmlTemplate html("username:{{ username }}\nparm.list[1]: {{parm.list[1][2] }} \nparm.key: {{ parm.key }}", 1);
    JSONObject obj = {
            {"username", 1234},
            {"parm", {
                                 {"key", "cde"},
                                 {"list", {1, {1,2.3, "abcd"}, "hahaha"}},
                         }}
    };
    html.setValue(obj);
    try {
        cout << html.render() << endl;
    } catch(exception& e) {
        cerr << e.what() << endl;
    }

    try {
        HtmlTemplate html("hello {{username}},\n"
                          "列表迭代如下\n"
                          "{% for x in list %}{{ x }}\n{%endfor%}"
                          "此时x已经是临时变量了，不可以在打印了 {{x}}\n"
                          "字典key迭代如下\n"
                          "{% for x in obj %}{{x}}\n{%endfor%}"
                          "字符串拼接\n"
                          "{{ a+b+c+\"abcdefg\" }}\n"
                          "循环if嵌套测试与复杂表达式\n"
                          "{%for x in list%}"
                          "{%if x %}"
                          "{{ x }}\n"
                          "{% for y in list2%}"
                          "{{x}} * {{y}} + 2 * 3 - 4 + {{x}} = {{ x*y+2*3-4+x }}\n"
                          "{% endfor %}"
                          "{% else %}"
                          "xy的值为空\n"
                          "{%endif%}"
                          "{% endfor%}"
                          "this is end ....", 1);
        JSONObject obj = OBJECT(
                KEYVALUE("username", "hhk"),
                KEYVALUE("list", LIST(1,2,3,4,5)),
                KEYVALUE("list2", LIST(1,2,3)),
                KEYVALUE("obj", OBJECT(
                        KEYVALUE("key1", "value1"),
                        KEYVALUE("key2", 222),
                        KEYVALUE("key3", 333),
                )),
                KEYVALUE("a", "111"),
                KEYVALUE("b", "222"),
                KEYVALUE("c", "333"),
        );
        cout << html.setValue(obj).render() << endl;
    }catch (exception& e) {
        cerr << e.what() << endl;
    }
}