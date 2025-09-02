# 天下一人力比較

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tenka1-2013-qualb/tasks/tenka1_2013_qualB_a

下記の文字列が標準入力から与えられる。問題文においてカズキ君の渡された文字列と同じである。

 ```

ABGGEGBCFEBFBAF
FFGFACCCECDGCDGAFFFACGDA
EEDCAEAFBDDEEDGGA
GDCAGFFAACBGEDBAFBCDECGAE
EDB
GADGADEDBCGABDDCBBDBEAD
GADBB
DFCE
BFGCGCBEDC
EDGADBGGDDFEEGGFDGCAFBFGFAAD
DDAEBGACDFDGDAB
EEDCECFFAE
ADDBEEABFEAB
FEEBFDGAADAE
GB
```

 辞書順比較で $ 7 $ 番目に小さい文字列を標準出力に $ 1 $ 行で出力せよ。  
 なお、行の終端には改行が必要である。

## 说明/提示

### 辞書順比較について

 天下一株式会社に勤めるカズキ君は、以下の文字列の中から辞書順比較で $ 7 $ 番目に小さいものを選ぶという仕事を言い渡された。

 あなたは唖然とするカズキ君を助けるためにプログラムを書いて、答えを見つけることにした。

- ABGGEGBCFEBFBAF
- FFGFACCCECDGCDGAFFFACGDA
- EEDCAEAFBDDEEDGGA
- GDCAGFFAACBGEDBAFBCDECGAE
- EDB
- GADGADEDBCGABDDCBBDBEAD
- GADBB
- DFCE
- BFGCGCBEDC
- EDGADBGGDDFEEGGFDGCAFBFGFAAD
- DDAEBGACDFDGDAB
- EEDCECFFAE
- ADDBEEABFEAB
- FEEBFDGAADAE
- GB

- - - - - -

 文字列 $ A $ に対して、 $ A_i $ で $ i $ 番目の文字を表し、 $ |A| $ で文字列 $ A $ の文字数を表すことにすると、文字列 $ A $ と文字列 $ B $ を辞書順比較で比較するとは、

- $ A_i\ \neq\ B_i $ となる最小の $ i $ $ (1\ \leq\ i\ \leq\ {\rm\ min}(|A|,\ |B|)) $に対して
- $ A_i\ であれば、文字列\ A $ は文字列 $ B $ より小さい
- $ A_i\ >\ B_i $ であれば、文字列 $ A $ は文字列 $ B $ より大きい

- そのような $ i $ が存在しなければ、文字数が少ない方を小さいとする

 として文字列 $ A $ と文字列 $ B $ の大小関係を決めることである。

 なお、アルファベットの大小関係は、 `A` $ \lt{} $ `B` $ \lt{} $ `C` $ \lt{} $ $ ... $ $ \lt{} $ `Y` $ \lt{} $ `Z` である。  
 例えば、 `AA`, `B`, `BA`, `AB`, `A` の中から辞書順比較で $ 3 $ 番目に小さいものは `AB`である。(`A` $ \lt{} $ `AA` $ \lt{} $ `AB` $ \lt{} $ `B` $ \lt{} $ `BA` である。)

# 题解

## 作者：stry (赞：6)

# 这题十分水，只有一个数据点，可直接输出
```cpp
#include<iostream>
using namespace std;
int main()
{
    cout<<"EDGADBGGDDFEEGGFDGCAFBFGFAAD";//直接输出
    return 0;
}
```


---

## 作者：林家三少 (赞：5)

$$\color{#dedede}\boxed{\color{black}\text{据说这题只有一个数据点|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~}}$$ 

但我们还是要正经的做一做的

思路很简单：sort+输出

代码：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
string st[7+10];
//定义字符串数组
bool cmp(string x,string y)
{
	return x>y;
}
//string的sort是一定要打cmp的
int main()
{
    for(int i=1;i<=15;i++)
    	cin>>st[i];  //输入
    //不要问我为什么循环15次
    sort(st+1,st+1+15,cmp);
    //排序
    cout<<st[9];  //输出
    //不要问我为什么输出第九个
    return 0;
    //完美结束
}
```


---

## 作者：zr太弱了 (赞：2)

本题题目很长然而中文翻译就一点点，所以代码很短，按照题意将若干字符串排序即可：

C++快排：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
string s[10002];
int main() {
    for (n=0;cin>>s[n];n++)
    sort(s,s+n);
    cout<<s[6]<<endl;
}
```
然而，提交过程中我发现了一个神奇的东西：

>本题只有一个数据点

所以本题的另一种AC方法:

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    cout<<"EDGADBGGDDFEEGGFDGCAFBFGFAAD";
    return 0;
}
```
接下来介绍几种输出比较方便的语言：

$PHP$：

```php
EDGADBGGDDFEEGGFDGCAFBFGFAAD
```
PHP相对于c++和java，它的输出语句实在是……TQL，可以把标签外字符直接输出

$python2$：

```python
print "EDGADBGGDDFEEGGFDGCAFBFGFAAD\n"
```
$python3$:

```python
print("EDGADBGGDDFEEGGFDGCAFBFGFAAD\n")
```


---

## 作者：da32s1da (赞：2)

由于本题要求字典序，自然而然的想到了Trie树。
```
#include<bits/stdc++.h>
#define N 10050
using namespace std;
int n,m,z,tot,bh[55];
char s[55],s1[55];
struct trie{int usd,cnt,cld[27];}tree[N];
void add(){     //向trie树中加单词
	int let=0,leth=strlen(s),rot=0;
	while(tree[rot].cld[s[let]-'A'])
	rot=tree[rot].cld[s[let]-'A'],let++;
	while(let^leth) rot=(tree[rot].cld[s[let]-'A']=++tot),let++;
	tree[rot].usd=1;tree[rot].cnt++;
}
void find(int u,int num){  //找
	for(int i=0;i^27;i++)  //枚举所有孩子
	if(tree[u].cld[i]){
		s1[num]=i+'A';   //存下字母
		if(tree[tree[u].cld[i]].usd) z+=tree[tree[u].cld[i]].cnt; //若此处有单词，统计数加。
		if(z>=7) {puts(s1);return;} //若统计次数大于等于7，输出。
		find(tree[u].cld[i],num+1); //找孩子所包含的字符串
		if(z>=7) return;  //搜过孩子后若已输出，返回。
	}s1[num]=0;  //字母清空
}
int main(){
	while(scanf("%s",s)!=EOF) add();  //读入
	find(0,0);  //找字典序第7大的。
	return 0;   //走人
}
```

---

## 作者：_Qer (赞：1)

给定一堆字符串，请输出其第7小的那个字符串

字符串的数量并没有给出，难度就大了一点，输出第7小的那个，难度又大了。

输入部分是比较棘手的点，我们可以按下面的方法来做

```cpp
	int n;//这个是计数器，计算输入了多少个字符串
	string s[100010];//字符串数组，也可以是char s[][]
    //因为没给字符串数量的上限，开大一点保险
    for (n = 0; cin >> s[n]; ++n) {}
    //循环输入，把所有的字符串输入进来
    //最后计数器的值一定是字符串的数量
```

然后排序部分直接一个sort搞定

输出也没有什么难的

```cpp
#include <bits/stdc++.h>//头文件中包含iostream, algorithm
using namespace std;
int n;//计数器
string s[100010];//字符串
int main() {
    for (n = 0; cin >> s[n]; ++n) {}//输入
    sort(s, s + n);//排序
    cout << s[6] << endl;//下标0开始，所以这里的s[6]其实就是第七个
    return 0;
}
```

---

## 作者：lsyx0918 (赞：1)

~~emem..........ememem~~

这道题就是让我们进行字符串排序，算是一道水题了

二话不说，上代码：
```cpp
#include<bits/stdc++.h>//尽量不要使用万能头
using namespace std;
string st[7+10];
//定义字符串数组
bool cmp(string x,string y)//字符串排序函数（一般这种函数我比较喜欢放主函数前面）string的sort是一定要打cmp的
{
    return x>y;
}
int main()//主函数
{
    for(int i=1;i<=15;i++)
    {
        cin>>st[i];  //输入
    }
    //不要问我为什么循环15次
    sort(st+1,st+1+15,cmp);//排序
    cout<<st[9]<<endl;  //输出
    //不要问我为什么输出第9个
    return 0;
    //结束
}
```
下面，声明提交注意事项：

**AT不换行，暴零两行泪！**

---

## 作者：Cambridge (赞：1)


小学生又来发题解了！

这道题我们直接输出"EDGADBGGDDFEEGGFDGCAFBFGFAAD"并换行即可。

在思路这块，最后写上：AT不换行，爆零两行泪。

    #include<iostream>
    #include<cstring>
    #include<cstdio>
    #include<cmath>
    #include<string>
    #include<cstdlib>
    #include<algorithm>//文件头不解释
    using namespace std;
    int main()
    {
        printf("EDGADBGGDDFEEGGFDGCAFBFGFAAD\n");//直接输出
        return 0;//要有好习惯
    }

好了，本蒟蒻就讲到这里，希望对读者有所帮助。
    

---

## 作者：CZQ_King (赞：0)

这题可以模拟。
```cpp
#include<bits/stdc++.h>
using namespace std;
string s[2019];
int i;
int main(){
    while(cin>>s[i])i++;//一直输入
    sort(s,s+i);//排一下序
    puts(s[6].c_str());//输出第七个
    return 0;
}
```
当然，看了这么多大佬的题解后，我发现居然只有一个数据点！

于是来一波``Python2&Perl``代码
```
print "EDGADBGGDDFEEGGFDGCAFBFGFAAD\n";
```

---

## 作者：迷失再黑夜里 (赞：0)

# 我发现这个题只有一个测试点，实在是坑!
## 上代码！！！
```cpp
#include<bits/stdc++.h>//万能头文件就不必解释
using namespace std;
int main()
{
     cout<<"EDGADBGGDDFEEGGFDGCAFBFGFAAD"<<endl;//这就是唯一的测试点!

    return 0;//华丽的结尾
}
```
# 这是本作者费劲心思才测出来的，~~请给过~~；


---

