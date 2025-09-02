# [ABC046D] AtCoDeerくんと変なじゃんけん

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc046/tasks/arc062_b

シカのAtCoDeerくんは友達のTopCoDeerくんとあるゲームをして対戦しています。 このゲームは $ N $ ターンからなります。各ターンではそれぞれのプレイヤーはじゃんけんのグーかパーを出します。ただし、各プレイヤーは次の条件を満たす必要があります。

(※) 各ターンの後で、(今までにパーを出した回数)$ ≦ $(今までにグーを出した回数) を満たす

このゲームでの各プレイヤーの得点は、(勝ったターンの数) $ - $ (負けたターンの数) です。 AtCoDeerくんは特殊能力を持っているので、ゲームが始まる前にTopCoDeerくんの出す $ N $ ターンの手を全て知ることが出来ました。 AtCoDeerくんの各ターンでの手を決めて、AtCoDeerくんの得点を最大化してください。 TopCoDeerくんの出す手の情報は文字列 $ s $ で与えられます。 $ s $ の $ i(1≦i≦N) $ 文字目が `g`のときは $ i $ ターン目でTopCoDeerくんがグーを出すことを、 `p`のときはパーを出すことを表します。

## 说明/提示

### 制約

- $ 1≦N≦10^5 $
- $ N=|s| $
- $ s $ の各文字は`g`か`p`
- $ s $ で表される手は、条件(※)を満たしている

### Sample Explanation 1

常に相手とあいこになるように手を出すことで、$ 0 $点を取ることができて、これが最大値です。

### Sample Explanation 2

例えばグー,パー,グー,パー,グー,グー,パー,パー,グー,パー と出すことで、 $ 3 $回勝って$ 1 $回負けているので得点は$ 2 $点になり、これが最大値です。

## 样例 #1

### 输入

```
gpg```

### 输出

```
0```

## 样例 #2

### 输入

```
ggppgggpgg```

### 输出

```
2```

# 题解

## 作者：QwQ蒟蒻wjr (赞：4)

冒昧地问一句，这题是被而已评分的吗？

显然你能选帕子就选帕子。

假设第一个人全出石头。

考虑把一些石头修改成帕子。

这样贡献只增不减，加起来就是答案。

```cpp
#include<cstdio>
#include<cstring>
#define re register
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	if(f)
		x=(~x)+1;
}
char s[1000010],len;
long long ans,sum_1,sum_2;
bool col[1000010];
int main()
{
	scanf("%s",s+1);
	len=strlen(s+1);
	for(int i=1; i<=len; ++i)
	{
		if(s[i]=='p')
		{
			if(sum_1<sum_2)
				sum_1++;
			else
			{
				sum_2++;
				ans--;
			}
		}
		else
		{
			if(sum_1<sum_2)
			{
				sum_1++;
				ans++;
			}
			else
				sum_2++;
		}
	}
	printf("%lld\n",ans);
}
```


---

## 作者：精神小伙！ (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT2141)

因为布总能赢石头，所以这个题只有一个原则：**能出布就出布**

但要注意 $ x_i \le y_i $ 的限制，它说明出石头的数量要大于出布的数量，如果出布的数量等于石头的数量，就必须出石头满足题目要求。

代码如下：


------------

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<string>
#include<cstring>
using namespace std;
string s;
int main()
{
	int ans=0;
    int x=0;//石头的数量 
	int y=0;//布的数量
	cin>>s;
	int len=s.size();
	for(int i=0;i<len;++i)
	{
		if(x==y)//题目规定，石头的数量大于等于布的数量，这时只能出石头
		{
			x++;
			if(s[i]=='p') ans--; //如果对手出布就减一分
			continue;
		} 
		y++;
		if(s[i]=='g') ans++;//如果对手出石头就加一分 
	} 
	cout<<ans<<endl;
	return 0;
}
```
求过

---

## 作者：zcl1024 (赞：1)

这道题是一道很基础的贪心  
只有一个原则：  
# 能出布就出布  
这个原则大家应该还是懂的，因为出布不会扣分，很有可能加分，而出石头就有可能扣分了

下面献上cpp&&pascal代码

```
#include <iostream>
#include <string>
using namespace std;
int main(){
    string a;
    cin>>a;
    int len=a.size();
    int i;
    int x=0,y=0,ans=0;
    for (i=0;i<len;i++){
        if (x==y){//根据规定，这时候只能出石头
            x++;
            if (a[i]=='p') ans--;//如果对方出布，就扣分
        }
        else{
            y++;
            if (a[i]=='g') ans++;//如果对方出石头，就加分
        }
    }
    cout<<ans<<endl;
    return 0;
}
```
------------------------
```
var i,j,n,m,x,y,ans:longint;
    a:string;
begin
  readln(a);
  n:=length(a);
  for i:=1 to n do
  if x=y then
  begin
    inc(x);
    if a[i]='p' then dec(ans);//如果对方出布，就扣分
  end
  else
  begin
    inc(y);
    if a[i]='g' then inc(ans);//如果对方出石头，就加分
  end;
  writeln(ans);
end.
```

---

## 作者：无意识躺枪人 (赞：1)

#### 不多说了，贪心，如果只能出石头 (即$x_i = y_i$)的时候当然只能出石头
#### 如果$\small \color{red} \text{ 能出布时就一定出布}$，才能保证得分最高
~~实在太水不想多说了~~

```c
#include<bits/stdc++.h>
using namespace std;
char a[100005];
int x=0,y=0,ans=0;
int main()
{
	cin>>a;
	for (int i=0;i<sizeof(a);i++)
	 if (x==y){x++; if(a[i]=='p') ans--;}    //只能出石头 
	 else{y++; if(a[i]=='g') ans++;}         //能出布就一定出
	printf("%d\n",ans);                      //AT题记得\n
	return 0;
}
```

这道题居然是紫题？~~趁早A掉~~

---

## 作者：Fire_Raku (赞：0)

### 题目分析：

根据题意，只能出石头或布，而无论是什么情况，出布总是比出石头要好的，因为如果出布，要么是平局，要么是赢，不会亏；而要是出石头，要么是平局，要么是输，可能会亏。**综上所述，该亏的总是会亏的，只要我们每次出的布的次数是一样的，无论出在哪里，得到的分数一定是一样的。**

所以，我们只要在 $x_i < y_i$ 的条件下，尽可能的多出布，这样我们得到的分数就是最大的。

然后，剩下的就是模拟了，只要没有越过 $x_i < y_i$ 的条件，我们就出布，并判断是否可以加分，等到了不能出布的时候，只能出石头，并判断是否会扣分。

### Code：

```cpp
#include<bits/stdc++.h>
using namespace std ;
int x , y , ans ; 
string s ;
int main(){
	cin >> s ;
	for(int i = 0 ; i < s.length() ; i++){ 
		if(x == y){ //判断是否超过条件
			x++ ; 
			if(s[i] == 'p') ans-- ; 
		}
		else{
			y++ ; 
			if(s[i] == 'g') ans++ ;
		}
	}
	cout << ans << endl ; //记得换行qwq
	return 0 ;
}
```

---

## 作者：happybob (赞：0)

其实想到算法就很容易了。

这道题只涉及到布和石头，没有剪刀。布可以包住石头，所以当对方是石头时，我们尽可能出布，但是就算出石头也不会扣分。如果对方是布，我们也尽可能出布，出布不加分不扣分，但出石头就扣分了！

同时也要注意 $\large x_i \ge y_i$ 的条件。

$\text{72ms}$ 代码（当前最优，无 $\text{O2}$）：

```cpp
#include <iostream>
#include <string>
using namespace std;

int main()
{
	string s;
	ios::sync_with_stdio(false);
	cin >> s;
	int ans = 0;
	int x_cnt = 0; // 石头数量
	int y_cnt = 0; // 布的数量
	int len = s.length() - 1;
	for (int i = 0; i <= len; i++)
	{
		if (s[i] == 'g')
		{
			if (y_cnt + 1 <= x_cnt)
			{
				ans++;
				y_cnt++;
			}
			else
			{
				x_cnt++;
			}
		}
		else
		{
			if (y_cnt + 1 <= x_cnt)
			{
				y_cnt++;
			}
			else
			{
				x_cnt++;
				ans--;
			}
		}
	}
	cout << ans << endl;
	return 0;
}
```


---

## 作者：珅肐 (赞：0)

来一篇非模拟做法:

首先我们要知道，只要石头和布出的个数确定，
出的顺序就对答案没有影响。

可以自己尝试一下.

那么我们只要知道对方出的石头和布的个数就好了。

其次我们可以很容易看出，这道题简单的贪心思想：出布一定比出石头优。

那么我们要使布的个数最多，出石头和布的个数也就确定了：

设总长度为$l$，布的个数为$l/2($向下取整$)$，石头的个数为$l-l/2($注意不可以写成$l/2$，想想为什么？$)$

答案为：$min($我出布的个数，对手出石头的个数$)-min($我出石头的个数，对手出布的个数$)$。

这两个$min$分别代表自己赢的局数和对手赢的局数，因为平局都不得分，所以可以不考虑

#### 代码奉上：
```cpp
#include<cstdio>
#include<cstring>
using namespace std;
char c[100007];
int main(){
	scanf("%s",c);int l=strlen(c),g=0;
	for(int i=0;i<l;++i)if(c[i]=='g')g++;
	printf("%d\n",min(l/2,g)-min(l-l/2,l-g));
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

看了一遍，没有Pascal的，就发一篇吧！

此题太水，怎么能称为紫题呢？（各人认为应该是橙题）

## 思路
### 1.输入
### 2.暴力模拟，能出布就出布（因为对方只能出石头和布）
### 3.输出

输入不用说了吧

步骤二有两种方法：

1.边做边出，

当x>=y+1时，出布，判断对手出了什么，

出石头就把ans+1，

否则不变，

最后把y+1,

否则出石头，判断对手出了什么，

出布就把ans-1，

否则不变，

最后把x+1

2.经过我们玄学的一番计算后，发现第一种方法后出的永远都是：石头，石头，布，石头，布，石头，布……

所以输入后直接就可以写出出的方案，再进行判断就可以了

输出ans

接下来献上Pascal代码
```
var s:string;
    i,len,x,y,ans:longint;
begin
 readln(s);
 len:=length(s);
 for i:=1 to len do
 begin
  if (x>=y+1) then begin inc(y); if (s[i]='g') then inc(ans); end
  else begin inc(x); if (s[i]='p') then dec(ans); end;
 end;
 writeln(ans);
end.
```
实在不会的那就算了，去看别的大佬的更简洁的算法吧（我是蒟蒻）

---

## 作者：Joeywu_1101 (赞：0)

题目很水啊。。。省选是哪里来的？

首先明确一点

把P用在对方G身上 然后自己G被对方P揍

 和
 
 把P用在对方P上抵消 然后G和G也抵消
 
 是一样的
 
---
再明确一点：
 
 n/2的P必须全部用掉否则就
 
 # 亏了！
 
---
## 解释的不清楚，

## 举个栗子：
---

### 对方P|G|G

自己G|P|G

自己G|G|P

得分都是 0

---

### 对方G|G|P|P|G

自己G|P|G|P|G

自己G|G|G|P|P

自己G|P|G|G|P

自己G|G|P|P|G

自己G|G|P|G|P

得分都是 0

---
### 对方G|G|G|G|P|P


自己 G|G|G|P|P|P

自己 G|G|P|G|P|P

自己 G|G|P|P|G|P

自己 G|P|G|G|P|P

自己 G|P|G|P|G|P

得分都是1

所以无脑GPGPGPGP模拟就行啦~~

# 代码

    #include<bits/stdc++.h>
    using namespace std;
    int main(){
        bool b=0;
        int n,ans=0;
        string s;
        cin>>s;
        n=s.size();
        for(int i=0;i<n;i++){
            bool t;
            b=!b;
            if(s[i]=='g'){
                t=1;
            }else if(s[i]=='p'){
                t=0;
            }
            if(t==b){
                continue;
            }else if(t==1&&b==0){
                ans++;
            }else{
                ans--;
            }
        }
        cout<<ans;
        return 0;
    }

---

## 作者：醉梦未苏 (赞：0)

~~题目挺水的~~

### 纯模拟(或贪心)

**设当前出了$y$个布**

1. 能出布就出布($y>0$),这样下去分可以最高

2. 出不了布就出石头(即$y<=0$)

```python
s=input() #输入对手出招的字符串
ans=0 #分数
y=0 #出布的次数
for i in range(len(s)): #一位一位地枚举
    if(s[i]=='g'): #对手出石头
        if(y>0): #可以出布
            ans=ans+1
            y=y-1 #初步次数-1
        else:
            y=y+1 #出石头
    else: #对手出布
        if(y>0): 
            y=y-1 #出布次数-1
        else:
            y=y+1 #你出了石头
            ans=ans-1 #扣一分
print(ans) #输出
            

```

---

## 作者：CZQ_King (赞：0)

这道题还算简单，几个$if$解决了。

------------
思路：我们可以一直出布，但是出的石头一定不能比布少。所以我们要把布出在对方出石头的时候，而把石头出在不能出布的时候。就是尽量不要让自己输。

------------
代码：
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
string a;//出拳方式用string记录
int g,p,w;//用于记录出拳，出布和分数
int main(){
    cin>>a;
    for(int i=0;i<a.length();i++){
        if(a[i]=='g'){//如果对方出石头
            if(g>=(p+1)){//先判断能不能出布
                w++;//如果能就把分数加一
                p++;//而且把出布的次数加一
            }
            else g++;//否则平局
        }
        else{//如果出布
            if(g>=(p+1))p++;//判断能不能出布，如果能，平局
            else{//不能出的话
                g++;//出拳的次数加一
                w--;//分数减一
            }
        }
    }
    cout<<w<<endl;//最后输出分数
    return 0;//结束
}
```

---

## 作者：南橙未熟k (赞：0)

~~当我看到这题是紫题时，眼睛瞬间亮了~~，一道纯
## 贪心
返回正题，刚看到此题以为是暴力，~~因为石头剪刀布的题目太多是暴力了~~，后来发现，只能出石头和布，所以——重点来了
## 能出布一定出布，因为布一定会胜。
知道这一点，我们就可以打代码了


------------
```pascal
var s:string;
    i,len,x,y,ans:longint;
begin
    readln(s);
    len:=length(s);
    for i:=1 to len do
    begin
        if (x>=y+1) then 
        begin
            inc(y); 
            if (s[i]='g') then inc(ans); 
        end//判断是x大还是y大
        else begin 
        	inc(x); 
            if (s[i]='p') then dec(ans); 
        end;
    end;
    writeln(ans);//枚举分数
end.
```


------------
~~不要脸的~~贴上我博客的地址
[https://www.luogu.org/blog/chky2/](https://www.luogu.org/blog/chky2/)
本人蒟蒻，代码巨丑，QAQ



---

