//
// Created by Administrator on 2019/3/30 0030.
//
#include <iostream>
#include "ejson.h"
#include "cjinja.h"

using namespace cJinja;
using namespace EasyJson;
using namespace std;

void test1() { // 变量和变量索引测试
    HtmlTemplate html("username:{{ username }}\n"
                      "parm.list[1]: {{parm.list[1][2] }} \n"
                      "parm.key: {{ parm.key }}",
                      1); // 参数1表示传入的是模版字符串，0表示传入的是文件名，默认为0
    JSONObject obj = {
            {"username", 1234},
            {"parm", {
                {"key", "cde"},
                {"list", {1, {1,2.3, "abcd"}, "hahaha"}},
            }}
    };
    html.setValue(obj);
    cout << html.render() << endl << endl;
}

void test2() { // 列表迭代测试
    HtmlTemplate html("{% for x in list %}{{ x }}\n{%endfor%}"
                      "此时x已经是临时变量了，不可以在打印了 {{x}}\n"
                      , 1);

    JSONObject obj = OBJECT(
            KEYVALUE("list", LIST(1,2,3,4,5))
    );
    cout << html.setValue(obj).render() << endl << endl;
}

void test3() { // 字符串拼接测试与表达式计算测试
    HtmlTemplate html("{{ a+b+c+\"abcdefg\" }}\n"
                      "{{x}} * {{y}} + 2 * 3 - 4 / {{x}} = {{ x*y+2*3-4/x }}\n",
                      1);
    JSONObject obj = OBJECT(
            KEYVALUE("a", "111"),
            KEYVALUE("b", "222"),
            KEYVALUE("c", "333"),
            KEYVALUE("x", 123),
            KEYVALUE("y", 456)
    );
    cout << html.setValue(obj).render() << endl << endl;
}

void test4() { // 循环嵌套与表达式计算测试
    HtmlTemplate html("{{x}} * {{y}} + 2 * 3 - 4 + {{x}} = {{ x*y+2*3-4+x }}\n", 1);
    JSONObject obj = OBJECT(
            KEYVALUE("x", 123),
            KEYVALUE("y", 456)
    );
    cout << html.setValue(obj).render() << endl << endl;
}
void test() {
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
}

int main() {
    test();
}