# Vladik and chat

## 题目描述

Recently Vladik discovered a new entertainment — coding bots for social networks. He would like to use machine learning in his bots so now he want to prepare some learning data for them.

At first, he need to download $ t $ chats. Vladik coded a script which should have downloaded the chats, however, something went wrong. In particular, some of the messages have no information of their sender. It is known that if a person sends several messages in a row, they all are merged into a single message. It means that there could not be two or more messages in a row with the same sender. Moreover, a sender never mention himself in his messages.

Vladik wants to recover senders of all the messages so that each two neighboring messages will have different senders and no sender will mention himself in his messages.

He has no idea of how to do this, and asks you for help. Help Vladik to recover senders in each of the chats!

## 样例 #1

### 输入

```
1
2
Vladik netman
2
?: Hello, Vladik!
?: Hi
```

### 输出

```
netman: Hello, Vladik!
Vladik: Hi
```

## 样例 #2

### 输入

```
1
2
netman vladik
3
netman:how are you?
?:wrong message
vladik:im fine
```

### 输出

```
Impossible
```

## 样例 #3

### 输入

```
2
3
netman vladik Fedosik
2
?: users are netman, vladik, Fedosik
vladik: something wrong with this chat
4
netman tigerrrrr banany2001 klinchuh
4
?: tigerrrrr, banany2001, klinchuh, my favourite team ever, are you ready?
klinchuh: yes, coach!
?: yes, netman
banany2001: yes of course.
```

### 输出

```
Impossible
netman: tigerrrrr, banany2001, klinchuh, my favourite team ever, are you ready?
klinchuh: yes, coach!
tigerrrrr: yes, netman
banany2001: yes of course.
```

# 题解

## 作者：Ryzen_9_9950X3D (赞：0)

看到还没人发这道题的题解，蒟蒻写了一个，大家勿喷！\
~~调了二十多天才调出来 QAQ~~
# 思路
我们可以将状态表示成一个表 $x$，$x_{i,j}$ 表示每一组数据的第 $i$ 条消息是否可能是输入的第 $j$ 个用户发送的（ $1$ 代表不可能， $0$ 代表可能）。\
若是第 $i$ 条消息由已知第 $y$ 个用户发送，则将 $x_{i,y}$ 标注为 $0$ ，将 $x_{i,j}（j \ne y）$ 标注为 $1$；\
否则：
+ 如果第 $j$ 个用户出现在消息内容中，或是上一条/下一条消息的发送者，将 $x_{i,j}$ 标记为 $1$；
+ 否则，将 $x_{i,j}$ 标记为 $0$。

（由于本题有SPJ，任何一种合法的方案都可以，我选择的是尽量输出靠前的用户，也可以过的 QAQ）
# 示例
## 示例 1
比如说，有下面一组样例：
```
1
2
Vladik netman
2
?: Hello, Vladik!
?: Hi
```
生成的表 $x$ 如下：\
$\begin{bmatrix} 1 & 0 \\ 0 & 1 \end{bmatrix}$\
不难看出，第一条消息对应的用户不可能是 Vladik，因为第一句话中提及过他的名字，而一个人的话中不能提及他的名字，同理，第二条消息对应的用户不可能是 netman。\
所以，第一条消息只有可能是 netman 发送的，第二条消息只有可能是 Vladik 发送的。
所以，输出如下：
```
netman: Hello, Vladik!
Vladik: Hi
```
## 示例 2
再举个例子：
```
1
2
netman vladik
3
netman:how are you?
?:wrong message
vladik:im fine
```
此时第一条消息是 netman 发的，第三条消息是 vladik 发的，第二条消息不可能是 netman 或 vladik 发的，因此，生成的表 $x$ 如下：\
$\begin{bmatrix} 0 & 1 \\ 1 & 1 \\ 1 & 0 \end{bmatrix}$\
第二条消息不可能是任何人发送的，因此无解，输出：
```
Impossible
```
# 代码
我们可以用类似的思路，得到下面的代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
string x;
struct chat
{
    string user,text;
};
bool f(string parent,string son)
{
    auto x = parent.find(son);
    bool a = (x != parent.npos),b = (x == 0 || !isalnum(parent[x - 1]) || !isalnum(son[0])),c = !isalnum(parent[x + son.size()] || !isalnum(son[son.size() - 1]));
    return a && b && c;
}
const char wc[] = {'\0',' ',',','.','!','?',':'};
bool s_o_c[105][105];
int o[105];
bool test(int users,int tests,int now,string user[],chat record[])
{
    if(now > tests)
    {
        for(int i = 1; i <= tests; i++)
        {
            printf("%s",user[o[i]].c_str());
            for(int j = 0;j < record[i].text.size() - 1;j++)
            {
                cout << record[i].text[j];
            }
            cout << endl;
        }
        return true;
    }
    for(int i = 1; i <= users; i++)
    {
        if(s_o_c[now][i] == false && i != o[now - 1])
        {
            o[now] = i;
            if(test(users,tests,now + 1,user,record) == true) return true;
        }
    }
    return false;
}
void solve()
{
    memset(s_o_c,0,sizeof(s_o_c));
    memset(o,0,sizeof(o));
    int a;
    cin >> a;
    getline(cin,x);
    string users[105];
    for(int i = 1; i <= a; i++)
    {
        cin >> users[i];
    }
    getline(cin,x);
    int b;
    cin >> b;
    getline(cin,x);
    chat record[105];
    for(int i = 1; i <= b; i++)
    {
        getline(cin,x);
        x = x + ' ';
        string z = "";
        int j;
        for(j = 0; x[j] != ':'; j++) z = z + x[j];
        record[i].user = z;
        z = "";
        for(int k = j; k < x.size(); k++) z = z + x[k];
        record[i].text = z;
    }
    for(int i = 1; i <= b; i++)
    {
        if(record[i].user == "?")
        {
            for(int j = 1; j <= a; j++)
            {
                for(int k = 0; k < 7; k++)
                {
                    for(int l = 0; l < 7; l++)
                    {
                        s_o_c[i][j] |= f(record[i].text,wc[k] + users[j] + wc[l]);
                    }
                }
            }
        }
        else
        {
            for(int j = 1; j <= a; j++)
            {
                if(users[j] == record[i].user)
                {
                    s_o_c[i][j] = 0;
                    s_o_c[i - 1][j] = s_o_c[i + 1][j] = 1;
                }
                else s_o_c[i][j] = 1;
            }
        }
    }
    int hv = 0;
    for(int i = 1;i <= b;i++)
    {
        for(int j = 1;j <= a;j++)
        {
            hv += s_o_c[i][j];
        }
        if(hv == a)
        {
            printf("Impossible\n");
            return;
        }
        hv = 0;
    }
    if(!test(a,b,1,users,record)) printf("Impossible\n");
}
int main()
{
    int a;
    cin >> a;
    getline(cin,x);
    while(a--) solve();
    return 0;
}
```

---

