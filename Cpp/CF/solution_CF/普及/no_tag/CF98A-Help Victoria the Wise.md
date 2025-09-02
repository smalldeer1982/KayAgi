# Help Victoria the Wise

## 题目描述

Vasilisa the Wise from a far away kingdom got a present from her friend Helga the Wise from a farther away kingdom. The present is a surprise box, yet Vasilisa the Wise doesn't know yet what the surprise actually is because she cannot open the box. She hopes that you can help her in that.

The box's lock is constructed like that. The box itself is represented by an absolutely perfect black cube with the identical deepening on each face (those are some foreign nanotechnologies that the far away kingdom scientists haven't dreamt of). The box is accompanied by six gems whose form matches the deepenings in the box's faces. The box can only be opened after it is correctly decorated by the gems, that is, when each deepening contains exactly one gem. Two ways of decorating the box are considered the same if they can be obtained one from the other one by arbitrarily rotating the box (note that the box is represented by a perfect nanotechnological cube)

Now Vasilisa the Wise wants to know by the given set of colors the following: in how many ways would she decorate the box in the worst case to open it? To answer this question it is useful to know that two gems of one color are indistinguishable from each other. Help Vasilisa to solve this challenging problem.

## 样例 #1

### 输入

```
YYYYYY
```

### 输出

```
1
```

## 样例 #2

### 输入

```
BOOOOB
```

### 输出

```
2
```

## 样例 #3

### 输入

```
ROYGBV
```

### 输出

```
30
```

# 题解

## 作者：ikunTLE (赞：11)

[题目传送门](https://www.luogu.com.cn/problem/CF98A)

### 思路

首先统计出每种字母出现的次数，然后将得到的序列非 $0$ 部分按升序排序。设这个序列为 $A$，答案为 $X$，打表得到的 $11$ 种情况分别是：
  
- 当 $A=\{6\}$ 时，$X=1$。
- 当 $A=\{1,5\}$ 时，$X=1$。
- 当 $A=\{2,4\}$ 时，$X=2$。
- 当 $A=\{3,3\}$ 时，$X=2$。
- 当 $A=\{1,1,4\}$ 时，$X=2$。
- 当 $A=\{1,2,3\}$ 时，$X=3$。
- 当 $A=\{2,2,2\}$ 时，$X=6$。
- 当 $A=\{1,1,1,3\}$ 时，$X=5$。
- 当 $A=\{1,1,2,2\}$ 时，$X=8$。
- 当 $A=\{1,1,1,1,2\}$ 时，$X=15$。
- 当 $A=\{1,1,1,1,1,1\}$ 时，$X=30$。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=2e6+10;
char s[10];
int tong[128],ans[N];
int main(){
	scanf("%s",s+1);
	for(int i=1;i<=6;++i)
		++tong[s[i]];
	int a[]={0,tong['R'],tong['O'],tong['Y'],tong['G'],tong['B'],tong['V'],0,0};
	sort(a+1,a+7);
	int x=0;
	for(int i=1;i<=6;++i)
		x=x*10+a[i];
	ans[6]=1;
	ans[15]=1; 
	ans[24]=2; 
	ans[33]=2;
	ans[114]=2;
	ans[123]=3;
	ans[222]=6;
	ans[1113]=5;
	ans[1122]=8;
	ans[11112]=15;
	ans[111111]=30;
	printf("%d\n",ans[x]);
	return 0;
}
```

---

## 作者：Mint_Flipped (赞：4)

没人写题解 我来一发。

这题就是求给你6个颜色，最多6种，给正方形涂色的方案数。

我们只要把每种情况的方案数算出来，直接就可以解得。

我来讲讲每种情况怎么算的：（建议dfs一下）

6 
6个面都是一种颜色 很明显只有一种。

15
只有一个面是另一种颜色，而且随意旋转，那么只有一种，因为放哪个面都一样。

24 
只有2这种颜色相邻和对位两种情况。

33
只有两两相邻和一个圈差一面两种情况。

114
只有1的两种颜色相邻和对位两种情况。

123
只有1，2两种颜色，两两相邻和一个圈差一面（112，121）三种情况

222
相邻，对位6种。

1113
...接下来 我也有点模糊，不记得当初是怎么想的了（还是dfs一下吧）。

111111
题目给了30种。

11112
可以从111111（30）推过去。

先上代码：

```c
#include <bits/stdc++.h>
#define ll long long
#define mem(a,b) memset(a,b,sizeof(a))
#define fo1(a,b) for(int a=0;a<b;++a)
#define fo2(a,b) for(int a=1;a<=b;++a)
#define inf 0x3f3f3f3f
using namespace std;
const int maxn=1e5+5;
const int mod=1e9+7;
int a[111115];
int b[10];
int main()
{
    //R,O,Y,G,B,V
    string s;
    cin>>s;
    fo1(i,6){
        if(s[i]=='R')
        b[1]++;
        else if(s[i]=='O')
        b[2]++;
        else if(s[i]=='Y')
        b[3]++;
        else if(s[i]=='G')
        b[4]++;
        else if(s[i]=='B')
        b[5]++;
        else
        b[6]++;
    }
    sort(b+1,b+7); 
    a[6]=1; //1种颜色
    a[15]=1; // 2种颜色 第1种有1个 第二种有5个
    a[24]=2; //...依此类推
    a[33]=2;
    a[114]=2;
    a[123]=3;
    a[222]=6;
    a[1113]=5;
    a[1122]=8;
    a[11112]=15;
    a[111111]=30;
    int ans=0;
    fo2(i,6)
    ans=ans*10+b[i];
    printf("%d\n",a[ans]);
    return 0;
}
```



---

## 作者：Elhaithan (赞：3)

## [题目传送门](https://www.luogu.com.cn/problem/CF98A)

## 题意 
有一个正方体，用六种颜色给他涂色，问有几种涂色情况。  
## 思路
六个面都是一个颜色时，只有**一**种情况。

五个面都是一个颜色，仅有一面颜色不同，也是**一**种情况。

四面同色，另外两个面是与之不同的颜色，也就只有涂在对面或相邻**两**种情况。

四面同色，而另外两面颜色各不相同，也是只有涂在对面或相邻**两**种情况。

三面同色，另外三面也同色，也是只有三面围成一圈和三面都在一角**两**种情况

之后就慢慢推就可以了，总共十一种情况。

## AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
char ch;
int num[7];//计数器
int chg=0;//转换器 
map <int,int> mp;//存储多种情况的值 
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

 	for(int i=1; i<=6; i++){
 		cin>>ch;
 		//判断字符
 		if(ch=='R') num[1]++;
 		else if(ch=='O') num[2]++;
 		else if(ch=='Y') num[3]++;
 		else if(ch=='G') num[4]++;
 		else if(ch=='B') num[5]++;
 		else if(ch=='V') num[6]++;
	}
	sort(num+1,num+7);//将计数器中的数排序 
	for(int i=1; i<=6; i++){
		chg=chg*10+num[i];//将计数器中的数转化为一个整数 
	}
	//多种情况的值
	mp[6]=1;
	mp[15]=1;
	mp[24]=2;
	mp[33]=2;
	mp[114]=2;
	mp[123]=3;
	mp[222]=6;
	mp[1113]=5;
	mp[1122]=8;
	mp[11112]=15;
	mp[111111]=30;
	cout<<mp[chg];//输出 
 	
 	return 0;
}

```




---

## 作者：_int123_ (赞：3)

题目：

# Help Victoria the Wise

## 题面翻译

在正方体的六面镶嵌给定颜色的宝石（相同颜色不区分），问最多有几种彼此不等价（即各种旋转过后看起来不一致）的方案。

## 题目描述

Vasilisa the Wise from a far away kingdom got a present from her friend Helga the Wise from a farther away kingdom. The present is a surprise box, yet Vasilisa the Wise doesn't know yet what the surprise actually is because she cannot open the box. She hopes that you can help her in that.

The box's lock is constructed like that. The box itself is represented by an absolutely perfect black cube with the identical deepening on each face (those are some foreign nanotechnologies that the far away kingdom scientists haven't dreamt of). The box is accompanied by six gems whose form matches the deepenings in the box's faces. The box can only be opened after it is correctly decorated by the gems, that is, when each deepening contains exactly one gem. Two ways of decorating the box are considered the same if they can be obtained one from the other one by arbitrarily rotating the box (note that the box is represented by a perfect nanotechnological cube)

Now Vasilisa the Wise wants to know by the given set of colors the following: in how many ways would she decorate the box in the worst case to open it? To answer this question it is useful to know that two gems of one color are indistinguishable from each other. Help Vasilisa to solve this challenging problem.

## 输入格式

The first line contains exactly $ 6 $ characters without spaces from the set {R, O, Y, G, B, V} — they are the colors of gems with which the box should be decorated.

## 输出格式

Print the required number of different ways to decorate the box.

## 样例 #1

### 样例输入 #1

```
YYYYYY
```

### 样例输出 #1

```
1
```

## 样例 #2

### 样例输入 #2

```
BOOOOB
```

### 样例输出 #2

```
2
```

## 样例 #3

### 样例输入 #3

```
ROYGBV
```

### 样例输出 #3

```
30
```



------------

## 思路：

#### 由题知，共 6 个面，6 个面，由数学知识知，总共有 11 种情况。

1. 六个面是一个颜色，只有一种情况。

2. 五个面是一个颜色，有一面的颜色不同，一种情况。

3. 四个面是一个颜色，另外两个面的颜色可相同可不同，它们有涂在对面或相邻各两种情况。

4. 三个面是一个颜色，另外三面也同色，也是只有三面环绕正方体 $\frac{3}{4}$ 圈和三面都在一角两种情况。

5. 三个面是一个颜色，另外三面有两种颜色，可以两两相邻和一个圈差一面，共三种情况。

6. 三个面是一个颜色，另外三面均不同色，由上，将两个同色的改一种颜色，共六种情况。

7. 后面的情况可以通过将上面的一种情况的某种颜色改成另一种颜色来得到，具体种类见代码。



------------

AC 代码：

```cpp
#include<bits/stdc++.h>//万能头文件 
using namespace std;
int b[10];//存字母数字 
int num;
string s;
int main()
{
    cin>>s;//输入 
    for(int i=0;i<=5;i++)//题目说了字母只有 ROYGBV 六个字母 ，输入并存入 b 数组。 
	{
        if(s[i]=='R') b[1]++;
        if(s[i]=='O') b[2]++;
        if(s[i]=='Y') b[3]++;
        if(s[i]=='G') b[4]++;
        if(s[i]=='B') b[5]++;
        if(s[i]=='V') b[6]++; 
    }
    sort(b+1,b+6+1);
    for(int i=1;i<=6;i++) num=num*10+b[i];//将字母转化为数字，存到 num 中，更好判断。 
    //多种情况分别判断，下面注释为颜色种数。 
    if(num==6) cout<<1;       //1
    if(num==15) cout<<1;      //2
    if(num==24) cout<<2;      //2
    if(num==33) cout<<2;      //2
    if(num==114) cout<<2;     //3
    if(num==123) cout<<3;     //3
    if(num==222) cout<<6;     //3
	if(num==1113) cout<<5;    //4
    if(num==1122) cout<<8;    //4
    if(num==11112) cout<<15;  //5
    if(num==111111) cout<<30; //6
	return 0;
}
```


---

## 作者：eric0928 (赞：2)

## [题目传送门](https://www.luogu.com.cn/problem/CF98A)

### 题意
给你六种颜色和一个正方体，问你有多少种染色方法。

### 思路
既然只有 $6$ 种颜色，那就有 $11$ 种方法去染色，我们只需要把每种情况判断一下就可以了。


~~~cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int b[10],sum;
string s;
signed main(){
    cin>>s;
    for(int i=0;i<=5;i++){
        if(s[i]=='R') b[1]++;
        if(s[i]=='O') b[2]++;
        if(s[i]=='Y') b[3]++;
        if(s[i]=='G') b[4]++;
        if(s[i]=='B') b[5]++;
        if(s[i]=='V') b[6]++; 
    }
    sort(1+b,b+7);
    for(int i=1;i<=6;i++){
        sum=sum*10+b[i];
    }
    if(sum==6) cout<<1;//一种颜色
    if(sum==15) cout<<1;//两种颜色
    if(sum==24) cout<<2;//两种颜色
    if(sum==33) cout<<2;//两种颜色
    if(sum==114) cout<<2;//三种颜色
    if(sum==123) cout<<3;//三种颜色
    if(sum==222) cout<<6;//三种颜色
    if(sum==1113) cout<<5;//四种颜色
    if(sum==1122) cout<<8;//四种颜色
    if(sum==11112) cout<<15;//五种颜色
    if(sum==111111) cout<<30;//六种颜色

}
~~~

---

## 作者：boluo2014 (赞：1)

### 前言
我这个蒟蒻太菜，~~只知道打表~~。
### 思路

观察题目，发现数据很小，只有 $6$。而题目规定了只有 $6$ 种字母。

其实，想要用什么算法来做这道题是有一定难度的，所以我在这里使用了打表的方法。但是，为了更加简洁一些，打表肯定需要优化。

#### 优化方法1：

由于字母与字母之间只需要考虑相同或不相同，所有字母都是同等的。我们只需要记录每个字母出现的次数，再进行计算。

#### 优化方法2：

出现个数的顺序没有关系，对答案完全不影响。

也就是说比如有 $4$ 个第一种字母和 $2$ 个第二种字母，那和有 $2$ 个第 $1$ 种字母和 $4$ 个第二种字母是一样的。

为了统一，我们排序即可。

#### 枚举个数

统计次数并且排序，我们需要枚举的可能性已经大大降低了。它们分别是：

第 $1$ 种：$\{6\}$，有 $1$ 种。

第 $2$ 种：$\{1,5\}$，有 $1$ 种。

第 $3$ 种：$\{2,4\}$，有 $2$ 种。

第 $4$ 种：$\{3,3\}$，有 $2$ 种。

第 $5$ 种：$\{1,1,4\}$，有 $2$ 种。

第 $6$ 种：$\{1,2,3\}$，有 $3$ 种。

第 $7$ 种：$\{2,2,2\}$，有 $6$ 种。

第 $8$ 种：$\{1,1,1,3\}$，有 $5$ 种。

第 $9$ 种：$\{1,1,2,2\}$，有 $8$ 种。

第 $10$ 种：$\{1,1,1,1,2\}$，有 $15$ 种。

第 $11$ 种：$\{1,1,1,1,1,1\}$，有 $30$ 种。

统计：

共 $11$ 种。

不过，有一个小问题：把个数全部判断一次，是不是过于累了，要写 $7$ 次。

#### 更方便

其他巨佬的代码都是转化成十进制再判断，而我小菊若的方法就更加菜了：

先判断位数，分为 $5$ 种情况，每种情况内再判断。


### 代码
```
#include<bits/stdc++.h>
using namespace std;
int c[26],a[7],i,cnt;
int main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	string s;
	cin>>s;
	for(i=0;i<6;i++){
		c[s[i]-'A']++;
	}
	for(i=0;i<26;i++){
		if(c[i]){
			cnt++;
			a[cnt]=c[i];
		}
	}
	sort(a+1,a+1+cnt);//排序‘
	//分类判断（我为了让代码简短写了一些奇奇怪怪的公式） 
	if(cnt<=2)cout<<cnt<<endl;
	if(cnt==3){
		if(a[1]==1)cout<<a[2]+1<<endl;
		else cout<<6<<endl;
	}
	if(cnt==4){
		cout<<(3-a[4])*3+5<<endl;
	}
	if(cnt==5)cout<<(3-a[5])*15<<endl;
	if(cnt==6)cout<<30<<endl;
	return 0;
}
```

会了吗？

---

## 作者：LNYZY (赞：0)

## 思路:
可以通过定义一个函数数组或者结构体数组，来分别表示 $24$ 种不同的旋转操作。每种旋转操作实际上是对表示正方体六个面的索引进行重新排列的一种映射关系。例如，绕某个面对角线旋转会将原来的某些面的位置交换到新的位置。  
六个面都是一个颜色，就只有一种情况。  
五个面都是一个颜色，有一面的颜色不同，也是一种情况。  
四个面都是一个颜色，另外两个面的颜色可相同也可不同，它们有涂在对面或相邻各两种情况。  
剩下的就不一一列举了。
这题很简单，就不给代码了。

---

## 作者：_zhaosihan_qwq_ (赞：0)

# 题解：CF98A Help Victoria the Wis
## 思路：
首先，我们先知道一共有多少种旋转方式。    
1. 绕面对角线旋转：$6$ 种方案。
2. 绕体对角线旋转：$6$ 种方案。
3. 绕棱中垂线旋转：$12$ 种方案。  

一共有 $6+6+12=24$ 种方案。  
那这样只要判断有几个面颜色一样，定一个变量 $n$，如果都一样用 $6$ 表示，$5$ 个一样用 $15$ 表示，那么假如有三种颜色，每种有 $2$ 个面，那么就用 $222$ 表示。
最后判断 $n$ 的大小对应的方案数。
- $n=6$：方案数为 $1$。
- $n=15$：方案数为 $1$。
- $n=24$：方案数为 $2$。
- $n=33$：方案数为 $2$。
- $n=114$：方案数为 $2$。
- $n=123$：方案数为 $3$。
- $n=222$：方案数为 $6$。
- $n=1113$：方案数为 $5$。
- $n=1122$：方案数为 $8$。
- $n=11112$：方案数为 $15$。
- $n=111111$：方案数为 $30$。

按照表格对应的颜色个数输出即可。

---

## 作者：Ghosty_Neutrino (赞：0)

## 题意

输入一个字符串，长度固定为 $6$ 。这个字符串表示所拥有的贴纸，现在要用这些贴纸去贴一个正方体，询问方案数（能通过旋转变成一模一样的算一种方案）。

## 分析

首先先要先知道对于一个已经涂好颜色的正方体，可以有 $24$ 中旋转方式：选择不同的面作为正面，故而有 $6$ 种，然后保持该面为正面，可以做 $4$ 次旋转（用手转），得 $24$。

第二步要对每个面编号。

然后我们可以暴力对一个正方体涂色得到一个字符串（以上面编号的顺序），然后再对它进行 $24$ 次旋转，得到 $24$ 个字符串，取字典序最小的作为当前涂的颜色的代表，存到某 set 去重，最后 set 大小为答案。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
const int INF = 0x3f3f3f3f;
const int mod = 1e9+7;
const int maxn =1e3+7;
const double pi = acos(-1.0);
const int v2 = (mod+1)/2;
const double eps = 5e-6;
char s[6],modle[6] = {'R','O','Y','G','B','V'};
int v[6];
int used[24][6] = {
    {1,2,3,4,5,6},{6,5,4,3,2,1},
    {1,3,4,5,2,6},{6,4,3,2,5,1},
    {1,4,5,2,3,6},{6,3,2,5,4,1},
    {1,5,2,3,4,6},{6,2,5,4,3,1},

    {2,6,3,1,5,4},{4,1,3,6,5,2},
    {2,3,1,5,6,4},{4,3,6,5,1,2},
    {2,1,5,6,3,4},{4,6,5,1,3,2},
    {2,5,6,3,1,4},{4,5,1,3,6,2},
    {3,2,6,4,1,5},{5,4,6,2,1,3},
    {3,6,4,1,2,5},{5,6,2,1,4,3},
    {3,4,1,2,6,5},{5,2,1,4,6,3},
    {3,1,2,6,4,5},{5,1,4,6,2,3},
};
set<string> st;
void did(string s){
    string res = s;
    for(int i = 0;i < 24;i++){
        string tmp = "";
        for(int j = 0;j < 6;j++) tmp+=s[used[i][j]-1];
        if(res.compare(tmp)>0) res = tmp;
    }
    st.insert(res);
}
void dfs(int now,string ns){
    if(now==6){
        did(ns);
        return ;
    }
    for(int i = 0;i < 6;i++){
        if(v[i]!=0){
            v[i]--;
            dfs(now+1,ns+modle[i]);
            v[i]++;
        }
    }
}
int main(){
    scanf("%s",s);
    for(int i = 0;i < 6;i++){
        for(int j = 0;j < 6;j++){
            if(modle[j]==s[i]){
                v[j]++;
            }
        }
    }
    dfs(0,"");
    cout<<st.size()<<endl;
    return 0;
}
```

---

