# 図書館 2 (Library 2)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joi2022yo2/tasks/joi2022_yo2_a

読書好きのビ太郎は図書館で本を借りて読むことにした．ビ太郎の家は狭いため，床には本 $ 1 $ 冊分の広さのスペースしかない．ただし高さは十分にあるため，ビ太郎はこのスペースに本を積んで管理することにした．

ビ太郎はこれから $ Q $ 回の行動を取る．$ i $ ($ 1\ \leqq\ i\ \leqq\ Q $) 回目の行動は文字列 $ S_i $ で表される．$ S_i $ は 英小文字からなる文字列か `READ` のいずれかであり，その意味は次の通りである．

- 英小文字からなる文字列の場合，ビ太郎は書名が $ S_i $ である本を図書館から借り，スペースの一番上に積む．
- `READ` の場合，ビ太郎はスペースの一番上に積まれている本を読み，図書館に返却する．

あなたはビ太郎がどの本をどのような順番で読んだのかを調べたい．

$ Q $ 回の行動の内容が与えられたとき，ビ太郎が読んだ本の書名を読んだ順に出力するプログラムを作成せよ．

## 说明/提示

### 制約

- $ 2\ \leqq\ Q\ \leqq\ 200\,000 $．
- $ Q $ は整数である．
- $ S_i $ は長さ $ 1 $ 以上 $ 10 $ 以下の文字列である ($ 1\ \leqq\ i\ \leqq\ Q $)．
- $ S_i $ は英小文字からなる文字列または `READ` である ($ 1\ \leqq\ i\ \leqq\ Q $)．
- $ S_i $ が `READ` であるような $ i $ ($ 1\ \leqq\ i\ \leqq\ Q $) は $ 1 $ つ以上存在する．
- $ S_i $ が `READ` のとき，必ずスペースに $ 1 $ 冊以上の本が存在する ($ 1\ \leqq\ i\ \leqq\ Q $) ．

### 小課題

1. ($ 40 $ 点) $ Q\ \leqq\ 2\,000 $．
2. ($ 60 $ 点) 追加の制約はない．

### 採点に関する注意

すべての提出はジャッジシステム上で採点される．

提出されたソースコードは，小課題に対応するすべての採点用入力データについて正しい結果を返したとき，その小課題について正解と認められる．

各提出の得点は，提出されたソースコードについて正解と認められた小課題の得点の合計である．

この課題の得点は，**この課題に対するすべての提出の得点の最大値**である．

現在の得点は「提出結果」タブの「自分の得点状況」から確認できる．

### Sample Explanation 1

この入力例ではビ太郎は以下のように行動する． 1. 書名が `joi` である本をスペースに積む．このとき，スペースに積まれている本の書名は `joi` となる． 2. 書名が `joig` である本をスペースに積む．このとき，スペースに積まれている本の書名は上から順に `joig` ，`joi` となる． 3. 書名が `ioi` である本をスペースに積む．このとき，スペースに積まれている本の書名は上から順に `ioi` ，`joig` ，`joi` となる． 4. 書名が `ioi` である本を読んで返却する．このとき，スペースに積まれている本の書名は上から順に `joig` ，`joi` となる． 5. 書名が `egoi` である本をスペースに積む．このとき，スペースに積まれている本の書名は上から順に `egoi` ，`joig` ，`joi` となる． 6. 書名が `egoi` である本を読んで返却する．このとき，スペースに積まれている本の書名は上から順に `joig` ，`joi` となる． 7. 書名が `joig` である本を読んで返却する．このとき，スペースに積まれている本の書名は `joi` となる． よってビ太郎が読んだ本の書名 `ioi` ，`egoi` ，`joig` を順に改行区切りで出力する． この入力例はすべての小課題の制約を満たす．

### Sample Explanation 2

この入力例はすべての小課題の制約を満たす．

## 样例 #1

### 输入

```
7
joi
joig
ioi
READ
egoi
READ
READ```

### 输出

```
ioi
egoi
joig```

## 样例 #2

### 输入

```
20
one
READ
two
three
four
five
six
seven
READ
eight
nine
READ
ten
eleven
READ
READ
twelve
READ
READ
READ```

### 输出

```
one
seven
nine
eleven
ten
twelve
eight
six```

# 题解

## 作者：saixingzhe (赞：3)

# 题意
有 $Q$ 个字符串，若不为 $\texttt{READ}$，新增一本名为这个字符串的书放在上一本书上面（若没有上一本书就直接放下）；否则取出最上面的一本书，输出它的名字。
# 思路
此题可以用栈模拟，因为栈是一个先进后出的容器，非常符合题目。当输入为 $\texttt{READ}$ 时，我们就将栈顶弹出，并输出栈顶，否则就将这本书压入栈。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int q;
string s;
stack<string>a;//创建一个字符串的栈
int main(){
    cin>>q;
    while(q--){
        cin>>s;
        if(s=="READ"){
            cout<<a.top()<<endl;//输出栈顶
            a.pop(); //弹出栈顶
        }
        else a.push(s);//将字符串压入栈
    }
    return 0;
}
```

---

## 作者：nr0728 (赞：2)

### 题意

有 $Q$ 个字符串，若不为 $\texttt{READ}$，新增一本名为这个字符串的书放在上一本书上面（若没有上一本书就直接放下）；否则取出最上面的一本书，输出它的名字。$(2\leq Q\leq 2\times10^5)$

### 题解

这道题可以直接用栈模拟。输入不为 $\texttt{READ}$，就将书压入栈；否则输出栈顶元素并弹出。C++ 可以用 $\text{STL}$ 中的 $\texttt{stack}$，节省不少代码。

$\textbf{Code:}$

```cpp
#include<bits/stdc++.h>
using namespace std;
int q; //代表题目中的 Q
string x;
stack<string>s; //创建一个类型为字符串的栈
int main()
{
    cin>>q;
    while(q--)
    {
        cin>>x; //此处数据范围 2*10^5 不会超时
        if(x=="READ") //若为 READ 输出栈顶
        {
            cout<<s.top()<<endl; //记得换行
            s.pop(); //弹出
        }
        else s.push(x);
    }
    return 0;
}
```

$$\sim\sim\textbf{END}\sim\sim$$

---

## 作者：small_john (赞：1)

## 分析

模拟题！！！

直接用栈。

先来认识一下栈吧！

```cpp
stack<数据类型> s//定义
s.empty()//判断栈是否为空
s.push(变量)//将变量压入栈
s.top()//返回栈顶
s.pop()//弹出栈顶
```

****

接下来就是具体做法：

1. 当 $Q$ 为 $\texttt {READ}$ 时，输出栈顶并弹出。

    ### code:

    ```cpp
    if(Q=="READ")
        cout<<s.top()<<'\n',s.pop();
    ```

2. 当 $Q$ 是其他字符串时，将 $Q$ 要入栈顶

    ### code:

    ```cpp
    else
        s.push(Q);
    ```

---

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
string Q;
stack<string> s;
int main()
{
    cin>>t;
    while(t--)
    {
        cin>>Q;
        if(Q=="READ")
            cout<<s.top()<<'\n',s.pop();
        else s.push(Q);
    }
    return 0;
}
```

---

## 作者：Leaves_xw (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_joi2022_yo2_a)

难度大概在普及-。

**题目大意：**

有 $Q$ 个字符串，若不为 $\texttt{READ}$，新增一本名为这个字符串的书放在上一本书上面（若没有上一本书就直接放下）；否则取出最上面的一本书，输出它的名字。$(2\leq Q\leq 2\times10^5)$

**思路：**

使用栈现进后出，后进先出的特点来做。如果遇到 $\texttt{READ}$，则输出栈顶，随后弹出栈即可。

**注意**：我们应当先判断是否为 $\texttt{READ}$，这样能够保证不使 $\texttt{READ}$ 入栈，方便操作，代码简单。

**AC 代码：**

```
#include<bits/stdc++.h>
using namespace std;
stack<string>st;//创建栈
int main()
{
   int q;
   cin>>q;
   for(int i=1;i<=q;i++)
   {
     string s;
     cin>>s;//循环时读入
     if(s=="READ")//判断是否为"READ"
     {
        cout<<st.top()<<endl;//输出当前栈顶
        st.pop();//弹出栈顶，防止重复
     }
     else
     {
        st.push(s);//否则将字符串s入栈
     }
   }
   return 0;
}
```



建议AC此题后做些[栈的练习](https://www.luogu.com.cn/problem/list?tag=287&page=1)。


---

## 作者：maomao233 (赞：0)

### 题意
有 $Q$ 个字符串，若不为 $\texttt{READ}$，新增一本名为这个字符串的书放在上一本书上面（若没有上一本书就直接放下）；否则取出最上面的一本书，输出它的名字。

### 分析
这题既说了要放书，又要取书，用普通的模拟非常难写。所以我们就可以用 $\texttt{C++}$ `STL` 库里的 `stack` 栈函数来写。每次输入的字符串，如果不为 $\texttt{READ}$，就把它压入栈里，否则就输出栈顶的元素就行了。因为都是按次序压入栈内的，所以越后放的越早出来。最后输出栈顶之后记得要把栈顶弹出。


------------

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
stack<string>stk;
int main()
{
	int q;
    cin>>q;
    while(q--)
	{
		string s;
        cin>>s;
        if(s=="READ")
		{
            cout<<stk.top()<<endl;
            stk.pop();
        }
        else 
		{
			stk.push(s);
		}
    }
    return 0;
}
```


---

## 作者：ruruo (赞：0)

# 写在前面

建议评分：普及-

建议标签：线性数据结构、栈

# 分析

- 直接用 $\text{STL}$ 中封装好的  $\texttt{stack}$ 模拟即可。

- 每次读入一个字符串 $S$ ，若 $S$ 为 `READ` ，输出栈顶元素，然后栈顶元素出栈，否则将 $S$ 入栈。

# 代码

```
#include<bits/stdc++.h>
using namespace std;

int main() {
    stack<string> s;
    int q;
    cin >> q;
    for(int i = 1; i <= q; i++){
        string ss;
        cin >> ss;
        if(ss == "READ"){
            cout << s.top() << endl;
            // 注意这里的顺序
            s.pop();
        }else s.push(ss);
    }
    return 0;
}
```


---

