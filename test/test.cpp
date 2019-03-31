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
    cout << "测试1: 变量和变量索引测试" << endl;
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
    cout << "测试2: 列表迭代测试" << endl;
    HtmlTemplate html("{% for x in list %}{{ x }}\n{%endfor%}"
                      "此时x已经是临时变量了，不可以在打印了 {{x}}\n"
                      , 1);

    JSONObject obj = OBJECT(
            KEYVALUE("list", LIST(1,2,3,4,5))
    );
    cout << html.setValue(obj).render() << endl << endl;
}

void test3() { // 字典迭代测试for-endfor
    cout << "测试3：字典迭代测试" << endl;
    HtmlTemplate html("{% for key in dict %}迭代1: 字典的key值为 {{ key }}\n{% endfor %}"
                      "{% for key,value in dict %}迭代2: 字典的key值为 {{ key }}, value值为 {{ value}}\n{% endfor %}"
                      "{% for ,value in dict %}迭代3: 字典的value值为 {{ value }}\n{% endfor %}", 1);
    JSONObject obj = OBJECT(
            KEYVALUE("dict", OBJECT(
                    KEYVALUE("key1", "value1"),
                    KEYVALUE("key2", 1234),
                    KEYVALUE("key3", nullptr),
            ))
    );
    cout << html.setValue(obj).render() << endl << endl;
}

void test4() { // 字符串拼接与表达式计算测试
    cout << "测试4: 字符串拼接与表达式计算测试" << endl;
    HtmlTemplate html("{{ a+b+c+\"444\" }}\n"
                      "{{x}} * {{y}} + 2 * 3 - 4 / {{x}} = {{ x*y+2*3-4/x }}\n",
                      1);
    JSONObject obj = OBJECT(
            KEYVALUE("a", "111"),
            KEYVALUE("b", "222"),
            KEYVALUE("c", "333"),
            KEYVALUE("x", 12),
            KEYVALUE("y", 34)
    );
    cout << html.setValue(obj).render() << endl << endl;
}

void test5() { // if-else-endif测试
    cout << "测试5: if-else-endif测试 " << endl;
    HtmlTemplate html("{% if 1==1 %} 1==1 成立 {% else %} 1==1不成立 {%endif %}\n"
                      "{% if !x %} x为空 {% else %} x不为空 {%endif %}\n"
                      "{% if x==2 %} x==2 成立 {% endif %}\n"
                      "{% if x+1!=2 %} x+1!=2 成立 {% endif %}\n"
                      "{% if x<3 %} x<3 成立 {% endif %}\n"
                      "{% if x>1 %} x>1 成立 {% endif %}\n"
                      "{% if str==\"abcd\" %} str为abcd {% endif %}\n"
                      "{% if 1 %} 常量表达式1 {% endif %}\n"
                      "{% if 0 %} 常量表达式0，此处不会输出 {%endif%}", 1);
    JSONObject obj = {
            {"x", 2},
            {"str", "abcd"}
    };
    cout << html.setValue(obj).render() << endl;
}

void test6() { // 循环嵌套测试
    cout << "测试6：循环嵌套" << endl;
    HtmlTemplate html("{%for x in list%}"
                        "{%if x %}"
                            "{% for y in list2%}"
                                "{{x}} * {{y}} = {{ x*y }}\n"
                            "{% endfor %}"
                        "{% else %}"
                            "x的值为空\n"
                        "{%endif%}"
                      "{% endfor%}", 1);
    JSONObject obj = OBJECT(
            KEYVALUE("list", LIST(1,2,3,4,5)),
            KEYVALUE("list2", LIST(1,2,3)),
    );
    cout << html.setValue(obj).render() << endl << endl;
}

void test7() { // 模版文件作为输入
    cout << "测试7: 模版文件输入测试" << endl;
    HtmlTemplate html("tmpl.html");
    JSONObject context = OBJECT(
            KEYVALUE("username", "hhk"),
            KEYVALUE("obj", OBJECT(
                    KEYVALUE("abcd", LIST(1,2.3, "hahahaha")),
                    KEYVALUE("obj", OBJECT(
                            KEYVALUE("key", "this is obj.obj.key' s value")
                    ))
            )),
            KEYVALUE("null", nullptr),
            KEYVALUE("list", LIST(1, "qwerty", 2.34, OBJECT(
                    KEYVALUE("key", "this is a key"),
                    KEYVALUE("key2", "this is a key2"),
            ))),
            KEYVALUE("list1", LIST(1,2,3,4,5)),
            KEYVALUE("list2", LIST(1,2,3)),
            KEYVALUE("obj2", OBJECT(
                    KEYVALUE("key1", "value1"),
                    KEYVALUE("key2", 222),
                    KEYVALUE("key3", 333),
            )),
            KEYVALUE("a", "111"),
            KEYVALUE("b", "222"),
            KEYVALUE("c", "333"),
    );
    FILE* f = fopen("output.html", "w"); // 写入到文件中
    string&& str = html.setValue(context).render();
    fwrite(str.c_str(), 1, str.size(), f);
    fclose(f);
}

void test8() {
    cout << "测试8: 模版异常测试" << endl;
    HtmlTemplate html("{% if 1 %} xxx ", 1);
    // 不传入context
    try {
        cout << html.render() << endl;
    } catch(exception& e) {
        cerr << e.what() << endl;
    }
    cout << endl;
}

int main() {
    auto tests = { test1, test2, test3, test4, test5, test6, test7, test8 };
    for(auto test: tests)
        test();
    cout << "测试运行结束" << endl;
}