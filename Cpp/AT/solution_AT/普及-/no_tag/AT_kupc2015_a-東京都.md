# 東京都

## 题目描述

[problemUrl]: https://atcoder.jp/contests/kupc2015/tasks/kupc2015_a

KUPC2015は[東京](https://atnd.org/events/70910)と[京都](https://atnd.org/events/70909)の二箇所でオンサイトが開催されている． あなたはKUPCの告知を手伝うことにした． 英小文字からなる文字列が印字されたテープがある．あなたはこのテープを文字同士の間でのみ好きなだけ自由に切ってもよい． あなたは`tokyo`か`kyoto`のいずれかの文字列を含むテープをなるべくたくさん作りたい．ただし，一旦切ったテープを後でくっつけることはできないものとする． 作る事ができる`tokyo`もしくは`kyoto`を含むテープの数の最大値を出力せよ．

## 说明/提示

### Sample Explanation 1

`higashikyoto`と書かれたテープは`kyoto`を含んでいるので，そのまま切り分けなくても目的のテープが $ 1 $ つ得られる． `kupconsitetokyotokyoto`と書かれたテープを{`kupconsitetokyo`, `to`, `kyoto`}と切り分けると，目的のテープが $ 2 $ つ得られる． どう切り分けても目的のテープが得られない場合も存在しうる．

## 样例 #1

### 输入

```
3
higashikyoto
kupconsitetokyotokyoto
goodluckandhavefun```

### 输出

```
1
2
0```

# 题解

## 作者：老彩笔 (赞：2)

题目大意就是求出一个字符串中tokyo和kyoto的个数。

看起来题目非常的简单，直接枚举就好了

但是还是有需要注意的地方：单纯的直接枚举的话可能会有**重复**的字符串计入到了答案里面。

这时候我们就要采取一些技巧。

思路：

枚举每个字符，将它及其后面的4个字符拿来一起判断
（因为tokyo和kyoto长度都是5），判断可以用两个bool型的变量来实现

如果有符合题意的，累加答案并且让指针向后移5位，这样能去掉重复的部分

枚举时还有几个小优化：

1.当剩下还没有枚举的字符串长度小于5时，可以直接结束 ，因为后面不可能再有符合题意的字符串


2.判断一个长度为5的子串是否符合题意时，若有一个字符不匹配就打上标记，如果tokyo和kyoto都有了标记，直接退出判断

代码有解释：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string s;//表示输入的字符串 
char s1[10]={'t','o','k','y','o'},s2[10]={'k','y','o','t','o'};//预处理出符合要求的两种字符串 
bool c1,c2;//c1表示有无第一种字符串，c2表示有无第二种 
int ans=0,k;//k是s1和s2的指针 
int main()
{
	cin>>n;
	while(n--)
	{
		cin>>s;
		ans=0;//记着清零答案 
		for(int i=0;i<s.length();i++)//枚举字符串的每一位字符 
		{
			if(i>s.length()-5)break;//如果剩下的字符串长度小于五,直接结束 
			c1=0,c2=0;k=0;//清零 标记和指针 
			for(int j=i;j<i+5;j++)
			{
				if(s[j]!=s1[k])c1=1;
				if(s[j]!=s2[k])c2=1;
				if(c1&&c2)break;//如果两种字符串都不符合直接退出枚举 
				k++;//改变指针 
			}
			if(!c1)//如果符合s1 
			{
				ans++;//答案加一 
				i+=4;//i指针直接加4,防止重复累加 
			}
			else if(!c2)//如果符合s2 
			{
				ans++;//同上 
				i+=4;
			}
		}
		cout<<ans<<'\n';//输出 
	}
	return 0;
}
```



---

## 作者：Blue_wonders (赞：2)

## 枚举模拟算法，比较容易实现
#### 这道题貌似没什么坑
#### 算法实现：
- 字符串输入
- 判断每个字符是否符合要求
 -     如果符合要求那么查找直接加5
 -   不符合那么就从下一个点继续查找
- 输出有几个符合的点

#### 下面附上简单AC代码
[AC代码评测情况](https://www.luogu.org/recordnew/show/16206608)
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int n,m;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        m=0;
        string s;
        cin>>s;//使用字符串输入
        int p=s.size();//p为字符串位数(.size()为求长度的函数)
        for(int j=0;j<p;j++){
            if(s[j]=='t'&&s[j+1]=='o'&&s[j+2]=='k'&&s[j+3]=='y'&&s[j+4]=='o'){//如果符合'tokyo'的情况
                j=j+4;//直接查找直接到最后一个o的下一位
                m++;//计数器m加一
            }
            else{
                if(s[j]=='k'&&s[j+1]=='y'&&s[j+2]=='o'&&s[j+3]=='t'&&s[j+4]=='o'){//如果不是'tokyo'的情况而是'kyoto'的情况
                    j=j+4;//同样直接查找最后一个o的下一位
                    m++;//计数器m也加一
                }
            }
        }
        cout<<m<<endl;输出m并换行
    }
    return 0;//结束
}
```
感谢能看我谢的题解！

---

## 作者：Cambridge (赞：0)


蒟蒻又来发题解了！

这道题其实也就是用个暴力来写题，我们采用左起点lo来枚举每一个可能的字符串，当子字符串的开头在母字符串的lo位置上时，我们判断他是不是tokyo或kyoto这两种字符串，如果是，ans++，然后lo往后移5；如果不是，则lo往后移1,一直类举到最后。代码如下：

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstdlib>
#include<algorithm>//文件头不解释
using namespace std;
long long n,ans;
string st;
int main()
{
    cin>>n;
    for(int i=1; i<=n; i++)
    {
    	cin>>st;
    	int lo=0,hi=4;//lo从0开始，具体用处看上方解释
    	while(hi<=st.size()-1)
    	{
    		if(st.substr(lo,5)=="tokyo"||st.substr(lo,5)=="kyoto")ans++,lo+=5,hi+=5;//如果截取出来的字符串符合要求
    		else lo++,hi++;//否则，往后移一位
		}
		cout<<ans<<endl;//输出，记得换行
		ans=0;//记得清零
	}
    return 0;
}
```

好了，本蒟蒻就讲到这里，希望对读者有所帮助。

---

## 作者：黄昏烟雨乱WA声 (赞：0)

## ~~我爱暴力（枚举）~~
数据范围比较小，所以用暴力枚举也不会爆炸

挨个搜索输入的字符串，如果找到了就直接跳过这个单词去搜索下面的

code：
```cpp
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	int n;
	cin>>n;
	int m[n]={0};
	for(int i=0;i<n;i++){//要判定n个字符串
	char c[101];
	cin>>c;
	int k=strlen(c);//找到字符串的长度
	for(int j=0;j<k;j++){
		if(c[j]=='t'&&c[j+1]=='o'&&c[j+2]=='k'&&c[j+3]=='y'&&c[j+4]=='o'){//寻找tokyo
			m[i]++;
			j=j+4;
		}
			if(c[j]=='k'&&c[j+1]=='y'&&c[j+2]=='o'&&c[j+3]=='t'&&c[j+4]=='o'){//寻找kyoto
			m[i]++;
			j=j+4;
		}
	}
	}
	for(int i=0;i<n;i++){
		cout<<m[i]<<"\n";
	}//最后再输出
	return 0;//快乐结束
}
```


---

## 作者：林家三少 (赞：0)

$$ \bold{\text{这是一道简单的枚举题}} $$

看一下数据范围，字符串数量<100，字符串长度<100

100*100<100000000

所以是可以双for的，然后双for里写什么也很清楚了

再所以就上...

$$\bold{\text{对了，这里给大家推荐一个偷懒/装B神器}}$$



	#define 改成的东西 原来需要打的东西
    
就比如：

	我要打cin>>n;
    我可以写上这个：
    #define c cin>>
    然后以后我就可以写
    cn;
    
神不神奇？(~~仅推荐给萌新，大佬勿喷~~

~~还有，我不是来凑字数的~~

废话说完了，代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#define ll long long
#define s string
#define c cin
#define co cout<<ans<<"\n"
#define f for
#define l st.size()
//就这样省掉了很多(shao)东西
//打很长的代码是很好用
using namespace std;
ll t,ans;
s st;
//定义
int main(){
	c>>t;
	f(int i=1;i<=t;i++){
		c>>st;
		for(int j=0;j<=l;j++){
			if(st[j]=='t'){//如果他是以't'开头的
				if(st[j+1]=='o'&&st[j+2]=='k'&&st[j+3]=='y'&&st[j+4]=='o'){
					ans++;
					j+=4;
                    //如果可以就执行这些
				}
			}
			if(st[j]=='k'){//如果他是以'k'开头的
				if(st[j+1]=='y'&&st[j+2]=='o'&&st[j+3]=='t'&&st[j+4]=='o'){
					ans++;
					j+=4;
                    //如果可以就执行这些
				}
			}
		}
		co;
        //输出+清零
		ans=0;
	}
	return 0;
}
```


---

## 作者：Siyuan (赞：0)

## 很简单的暴力枚举题！

```
#include<iostream>
#include<string>
using namespace std;

int main()
{
    int T;  cin>>T;
    string s;
    while(T--)
    {
        int len,ans=0;
        cin>>s;  len=s.length();
        for(int i=0;i<len;i++)
            if((s[i]=='t'&&s[i+1]=='o'&&s[i+2]=='k'&&s[i+3]=='y'&&s[i+4]=='o')||(s[i]=='k'&&s[i+1]=='y'&&s[i+2]=='o'&&s[i+3]=='t'&&s[i+4]=='o'))
                ans++,i+=4;
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：勘探员·引魂人 (赞：0)

**前言：大家都知道，東京是岛国的首都，所以刷这道“AT1529 【東京都】”是对岛国题的尊重**

**思路：用字符串截取函数截取“st.substr(i,5)”，然后判断是否=="tokyo"或"kyoto"，若符合：个数++，每处理完就输出个数，输出完个数记得清0**

```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<cstring>//文件头哦，您太难喽
using namespace std;
string st;//定义字符串
int l,zt,n;//定义某些变量
int main()
{
	scanf("%d",&n);//输入n
	for(int j=1;j<=n;j++)//从1~n循环
	{
		cin>>st;//输入字符串
		l=st.size();//先截取个长度
		for(int i=0;i<l-5+1;i++)//从0~l-5+1循环
		{
			if(st.substr(i,5)=="tokyo"||st.substr(i,5)=="kyoto") zt++,i+=4;//截取“st.substr(i,5)”，然后判断是否=="tokyo"或"kyoto",若符合：个数++,i+=4
		}
		cout<<zt<<endl;//输出个数（换行！）
		zt=0;//个数清0
	}
	
	return 0;//结束“Caption at 1529 [capital of Tokyo]”
}
```


---

