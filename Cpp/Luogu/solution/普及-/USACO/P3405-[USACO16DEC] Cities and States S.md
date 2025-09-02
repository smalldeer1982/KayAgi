# [USACO16DEC] Cities and States S

## 题目描述

Farmer John 有若干头奶牛。为了训练奶牛们的智力，Farmer John 在谷仓的墙上放了一张美国地图。地图上表明了每个城市及其所在州的代码（前两位大写字母）。

由于奶牛在谷仓里花了很多时间看这张地图，他们开始注意到一些奇怪的关系。例如，FLINT 的前两个字母就是 MIAMI 所在的 `FL` 州，MIAMI 的前两个字母则是 FLINT 所在的 `MI` 州。  
确切地说，对于两个城市，它们的前两个字母互为对方所在州的名称。

我们称两个城市是一个一对「特殊」的城市，如果他们具有上面的特性，并且来自不同的州。对于总共 $N$ 座城市，奶牛想知道有多少对「特殊」的城市存在。请帮助他们解决这个有趣的地理难题！  

## 说明/提示

### 数据规模与约定

对于 $100\%$ 的数据，$1 \leq N \leq 2 \times 10 ^ 5$，城市名称长度不超过 $10$。

## 样例 #1

### 输入

```
6
MIAMI FL
DALLAS TX
FLINT MI
CLEMSON SC
BOSTON MA
ORLANDO FL```

### 输出

```
1```

# 题解

## 作者：NKU_AI_HMX (赞：78)

### 这篇题解主要为不太清楚map用法的同学服务，这题用数组即可。（不会map还是尽快学会，可问度娘，或者写一下[线性表](https://www.luogu.com.cn/training/113#problems)）
#### 主体思路和楼下楼上的大佬一样，先读取输入的两个字符串，然后选取他们各自的第一位第二位组成一个26进制数，然后通过判断数是否相等来判断是否符合要求，这里需注意，城市前两个字母和省的字母相同的情况。
```cpp
#include<bits/stdc++.h>
using namespace std;
int city[676][676], n, x, y, ans;//x表示城市前两个字母的26进制下的数，y是省份的。数相等则对应的省的两个字母和城市的前两个字母就相等。
int main() {
    string a, b;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>a>>b;
        x = (a[0] - 'A') * 26 + a[1] - 'A';//不减的话数据太大，数组开不了那么大（map的优势） 
        y = (b[0] - 'A') * 26 + b[1] - 'A';
        if (x != y) {//x==y的话如果要配对的话只会配到自己省。题目说了不在同一省，所以要排除。
            city[x][y]++;
            ans += city[y][x];
        }
    }
    cout<<ans;
    return 0;
}
```


---

## 作者：小手冰凉 (赞：44)

事实上楼下REDBAGdalao的做法还是麻烦了


map大法好啊


把州和城市的前两位分别提取出来hash，然后存到map里


注意州和城市的前两位相同时要加上特判




```cpp
#include<bits/stdc++.h>
using namespace std;
map<int,int>mmp[100005];
int n,ans;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        string a,b;
        cin>>a>>b;
        int A=a[0]*26+a[1];
        int B=b[0]*26+b[1];
        ans+=mmp[B][A];
        if(A==B)ans-=mmp[A][B];
        mmp[A][B]++;
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：DrownedFish (赞：30)

### 神奇的 substr 

我们都知道，奶牛找对应城市时都只看城市名字的前两位，所以城市名字后面那几位都是没用的。而且很烦。

就在这时，**substr（字符串子串）** 出现了！


```
举个例子，我们先定义个 string c="ABCDE";
那么 c.substr(0,2) 就是 "AB"。

是不是有点感觉了？其实它的意思就是：
- 从字符串 c 的第 0 位开始，按顺序取 2 位得到的子串。

如果你只写前面那个数字，而不写后面那个数字的话，
如 c.substr(1) 意思是：
- 从字符串 c 的第 1 位开始，一直到末尾的这段子串（这个例子中是"BCDE"）。

```

很奇妙吧，可以自己写程序试一下。

------------

### 思路

如果把 map 看成一个盒子，把对应城市对答案的贡献看成金币，那么想象一下：

```
有一天，叫做 MIAMI FL 的城市找到了很多盒子，
它高兴地打开 MIFL（由城市名前两位和州名拼接而成）盒子，
发现里面什么也没有，他很沮丧。

善良的 MIAMI FL 为了不让别的城市和它一样，
向 FLMI（由州名和城市名前两位拼接而成）盒子
放入了它仅有的一个金币，
和它有缘（对应）的城市将会得到这份好运。

不久之后，城市 FLINT MI 也来到了这个有很多盒子的地方，
它高兴地打开 FLMI 盒子，发现里面居然有一个金币！
它取走了这个金币，并且把它交给了 ans 国王。
怀着感激之情的它向 MIFL 盒子里也放了一枚金币。

这个故事在各个城市间流传开来，
每个城市都像他们一样以这种方式行动。
城市们的善举打动了盒子，
于是放进盒子的金币即使被拿走，也从来不会减少。
在 ans 的领导下，城市们都过上了富裕的生活。
```

有了 substr 的帮助，我们可以直接把城市名转化为它的前两个字符。之后把新城市名和州用两种顺序拼接起来，就得到了：取金币的盒子，放金币的盒子。

ans（交给国王的金币总数）就是最终对应城市的数量。（想一想为什么）

------------

### 代码


```C++
#include<bits/stdc++.h>
using namespace std;
int n,ans;           //城市数 金币总数/答案
string a,b;          //城市名 州名 
map<string,int> box; //神奇的 map 
int main()
{
	ios::sync_with_stdio(false); //增加 cin, cout 的速度 
	cin>>n;    //城市数量 
	while(n--) //重复 n 次 
	{
		cin>>a>>b;       //城市名 和 州名 
		a=a.substr(0,2); //取城市名称的前两位 
		if(a!=b)         //特判 不能自己跟自己对应 
		ans+=box[a+b];   //取得金币/答案贡献
		box[b+a]++;      //存入金币，造福 城州名恰好相反的城市 
	}
	cout<<ans<<endl;
	return 0;
}

```

------------

~~其实那个故事是我随便编的，而且有逻辑谬误，大家随便看看理解一下就好。~~

~~为什么我想起了那个一大片宏定义的神仙题解。~~


---

## 作者：fmj_123 (赞：13)

  蒟蒻表示不会用map，于是想出这种奇特解。
  
  考虑因为城市名只有前两位对我们有用，所以城市名可以只保留前两个字母。那么，我们可以**把城市名的两个字母与州名的两个字母分别转成数字，再拼接起来**
  
  如：AAAA转换成00000000，ZZZZ转换成26262626。
  
  显然，我们可以用数组储存 转换为某一个数的 个数，当我们寻找某一个城市的特殊城市对时，数组中”把州名和城市颠倒后组成的字符串所转成的数“里面的数就是答案。
  
  贴代码
  ```
  //不要在意头文件
#include<iostream>
#include<fstream>
#include<algorithm>
using namespace std;
long long n,ans;
int co[28282828]={0};
string c,p;
int stos(string st)//把字符串转为数字
{
    int s=0;
    for (int i=0;i<st.size();i++)
    {
        s=s*100+(st[i]-65);
    }
    return s;
}
int main()
{
    cin>>n;
    for (int i=1;i<=n;i++)
    {
      cin>>c>>p;
      c=c.substr(0,2);//城市名只保留前两位
      int x=stos(c),y=stos(p);
      if (co[y*10000+x]&&y!=x) ans+=co[y*10000+x];
      //累加与前面城市的特殊城市对数
      co[x*10000+y]++;//把拼接成的数记录下来
    }
    cout<<ans<<endl;
    return 0;
}

```
[提交记录](https://www.luogu.org/record/show?rid=6176091)

用时660ms, 内存11253KB

---

## 作者：cryozwq (赞：12)

这是本蒟蒻的第一篇题解，不喜勿喷。

看了一下各位 dalao 的解法，绝大部分是用的 map 做，并把字符串转换成数字，这里提供一个直接用字符串的 map 解法。

### 题目分析
题目的大致意思是：求有多少对城市和州满足城市的前两个字母与另一个州的前两个字母相同(~~好像还是很绕~~)，也就是令每个城市和他所在的州的前两个字母为 $c_i$ 和 $s_i$,找出一对 m 和 n 使得 $s_m=c_n$ 且 $s_n=c_m$。

看到这道题，第一反应是用 map 做，所以有以下代码：
~~~cpp
map<string,int>t;
~~~
其中 string 的那一项表示城市和州，int 项表示出现次数。

然后我就发现一个问题，如何表示城市和州呢？

经过我~~一通瞎搞~~深思熟虑后，我用的是这样的表示方法：在 $c_i$ 和 $s_i$ 中间插入空格，代码：
~~~cpp
	c2=c[0];c2+=c[1];//c2表示输入的c的前两位
	s2=s[0];s2+=s[1];//s2表示输入的s的前两位
	c1=c2;c1+=" ";c1+=s2;//c1表示合并c和s的结果
	s1=s2;s1+=" ";s1+=c2;//s1表示合并s和c的结果
~~~
下面开始说主体思路：对于输入的$c_i$与$s_i$，求出 $c1,c2,s1,s2$ 后，将答案加上 $t[s1]$，为啥加 $s1$ 不加 $c1$ 呢，因为一座城和州对应的应该是（州，城），然后 $t[c1]++$，最后输出答案即可。

然而，交上去 WA 了。。。

**这个题坑的地方就是要特判 $c2 = s2$，如果 $c2 = s2$ 就要把它减回去。**
### 完整代码
~~~cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	map<string,int>t;
	string c,s,c1,s1,c2,s2;
	int n,ans=0;
	cin>>n;
	while(n--)
	{ 
		cin>>c>>s;
		c2=c[0];c2+=c[1];//c2表示输入的c的前两位
		s2=s[0];s2+=s[1];//s2表示输入的s的前两位
		c1=c2;c1+=" ";c1+=s2;//c1表示合并c和s的结果
		s1=s2;s1+=" ";s1+=c2;//s1表示合并s和c的结果
		ans+=t[s1];
		if(c2==s2)//特判
		ans-=t[c1];
		t[c1]++;
	}
	cout<<ans<<endl;
    	return 0;
} 
~~~

---

## 作者：HsKr (赞：7)

感觉现有的几篇都不是特别详细啊。

首先想到：对于第一个字符串，除了前面两个字符，后面的一大串都是没有用的。

思路：输入时查询，如果有与其对应的就加上。

那么如何查找呢，考虑用二维`map`，即`map`套`map`，或`map`数组。

考虑将两个字符弄进`map`不便，于是就要将其压缩成数字，这里类似 字符串Hash 的做法，第一个字符乘以base加上第二个字符，可以用`map`存储。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<map>
using namespace std;
int n,ans=0,base=100;
string s,t;
map<int,map<int,int> > m;
int main(){
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>s>>t;
		int S=s[0]*base+s[1],T=t[0]*base+t[1];//将两个字符转化成数字 
		if(S!=T){//特判，如果省市开头相同，不符合条件 
			ans+=m[T][S];//有对应的就加上 
			m[S][T]++;//记录 
		}
	}
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：KaguyaH (赞：4)

[**题目传送门**](https://www.luogu.com.cn/problem/P3405) [**博客查看**](https://www.luogu.com.cn/blog/236807/Solution-luogu-P3405)

### 题意翻译

给定 $n$ 组由大写字母组成的字符串 $(a_i, b_i)$，定义 $sub(s)$ 为由 $s$ 的前两位组成的子串，求有多少对 $(i, j)$，使 $sub(a_i) = sub(b_j) \land sub(b_i) = sub(a_j) \land sub(a_i) \ne sub(b_i)$ 成立。

### 题目分析

由于题目中只要求前两位，所以我们不必哈希，把原串的前两位当成一个两位 $26$ 进制数即可。这里由于空间足够，可以当成 $32$ 进制数，利用位运算简化代码。

### 代码

```cpp
# define _CRT_SECURE_NO_WARNINGS
# include <cstdio>

typedef short unsigned int hu;
typedef long unsigned int lu;
typedef long long unsigned int llu;

static lu n;
static lu c[1 << 20]; // 4位，2^5进制，故开到2^20
static llu ans(0);

signed int main() {
	scanf("%lu", &n);
	for (register lu i(0); i < n; ++i) {
		static char a[11], b[3]; scanf("%s%s", a, b);
		const hu x(a[0] - 'A' << 5 bitor a[1] - 'A'), y(b[0] - 'A' << 5 bitor b[1] - 'A');
		if (x == y) continue;
		//printf("%hu %hu\n", x, y);
		ans += c[y << 10 | x],
		++c[x << 10 | y];
	}
	printf("%llu\n", ans);
	return 0;
}
```

---

## 作者：lytqwq (赞：4)


因为城市只有前两个字母有用，省份只有两个字母，我们直接 开 一个四维数组储存每种组合有多少种，然后再把省份和城市反过来统计答案即可。

注意：根据题意，当（省份)和（城市的前两个字母）都相同时，对答案贡献为0，所以特判一下就行了。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 200001
int n;
char a[N][11],b[N][3];
int c[27][27][27][27],d[N];
int ans;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",a[i]);
		scanf("%s",b[i]);
		if(a[i][0]==b[i][0]&&a[i][1]==b[i][1])
		{
			d[i]++;
		}
		c[a[i][0]-'A'][a[i][1]-'A'][b[i][0]-'A'][b[i][1]-'A']++;
	}
	for(int i=1;i<=n;i++)
	{
	    if(d[i]==0)
		ans+=c[b[i][0]-'A'][b[i][1]-'A'][a[i][0]-'A'][a[i][1]-'A'];
	}
	printf("%d\n",ans/2);//对于每个组合，我们统计了两遍，所以除2
}
```



---

## 作者：zylll (赞：3)

看到数据范围，考虑$O(n)$做法。

考虑变换储存方式，用$map$存储城市名称的前两位+州名称。

若满足条件，则前两位与后两位存在交换关系。

然后$O(n)$处理，统计答案即可。

别忘了统计一次答案后要减少一次$map$函数里的次数，避免重复统计。

```cpp
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#define pb(a) push_back(a)
#define mp(a,b) make_pair(a,b)
using namespace std;
int n,ans;
string s,t,s1;
vector<pair<string,string> > vec;
map<string,int> mapp;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        s.clear();t.clear(),s1.clear();
        cin>>s>>t;
        s1=s.substr(0,2);
        if(s1==t) continue;
        vec.pb(mp(s1,t));
        mapp[t+s1]++;
    }
    s.clear();t.clear();
    for(int i=0;i<(int)vec.size();i++){
        s=vec[i].first,t=vec[i].second;
        ans+=mapp[s+t];
        mapp[t+s]--;
    }
    printf("%d\n",ans);
    return 0;
}
```


---

## 作者：TESJackeyLove (赞：2)

# map嵌套大法好~ 
**昨天刚用map嵌套过了一道题，今天又碰到了可以用嵌套map解决的题了~**
```cpp
	map<int,map<int,int> >m;
```
- 个人觉得，嵌套map可以用于尝试解决二维数组炸下标的题。这里定义一个名为m的嵌套map，然后m[i][j]表示什么呢？字符串嘛，我们给它转化一下，因为只涉及到前两位字母（大写字母ascii码不超过100），所以我们可以用第一位字母的ascii码乘以100+第二位字母的ascii码作为下标表示这个字符串。那么第一维的i就是前面字符串转换后的结果，第二维的j就是后面字符串转换后的结果。那么m[i][j]就表示(i,j)这一对出现的次数。
- 我们可以边输入边操作，如果当前的两个字符串转换后是(i,j)，那么它就可以和(j,i)构成一对特殊城市，所以此时答案加上m[j][i]就可以了。
- 一个需要注意的点就是判别i==j，加上又要减去，不如不加。以下是代码：
```cpp
  #include<iostream>
  #include<cstdio>
  #include<cmath>
  #include<algorithm>
  #include<cstring>
  #include<map>
  #include<vector>
  #include<queue>
  #include<stack>
  #include<set>
  #define fore(i,a,b) for(register int i=a;i<=b;i++)
  #define foru(i,a,b) for(register int i=a;i<b;i++)
  #define ford(i,a,b) for(register int i=a;i>=b;i--)
  #define IGNB std::ios::sync_with_stdio(false);
  #define ll long long
  #define INF 0x3fffffff
  using namespace std;
  map<int,map<int,int> >m;
  string x,y;
  int main(){
      IGNB;
      int n,cnt=0;
      cin>>n;
      fore(i,1,n){
          cin>>x>>y;
          int x1=x[0]*100+x[1];
          int y1=y[0]*100+y[1];
          if(x1!=y1){
              cnt+=m[y1][x1];
              m[x1][y1]++;
          }	
      }
      cout<<cnt;
      return 0;
  }

```


---

## 作者：fangxk2003 (赞：1)

I ❤ luogu

我可是把多年积蓄的题解都贡献给洛谷了啊


进入正题。

这道题就是让你求有有多少对城市和州满足城市的前两个字母和州的两个字母刚好相反，即两个城市的前两个字母分别与另一个州的两个字母相等。

注意：“且来自不同的州”说明两个城市的前两个字母与州的两个字母不能全相等！

【算法分析】

这道题有点哈希的意思。

不难想到将这两个字母全都转化为正整数，设这两个字母为ch1,ch2，则s=(ord(ch1)-65)\*26+ord(ch2)-64;

于是就只要找两个数位子相反就好了。

因为 ，a>0,b>0，所以方程有唯一解。

设处理后，城市的前两个字母变成的正整数是a[i]，州的两个字母变成的正整数是b[i]，f1[i]=a[i]-b[i],f2[i]=a[i]\*b[i],当f1为相反数，f2相等时，说明这两个城市满足条件。于是就只要以f2为关键字从小到大排序，再用一个数组标记就好了。

注意：当f1=0时说明城市的前两个字母与州的两个字母相等，不能算进去！

【参考程序】

```cpp
var n,i,ans:longint;
    a,b,f1,f2:array[1..200000]of longint;
    f:array[-700..700]of longint;
    st:string;
procedure sort(l,r:longint);//快排
var i,j,x,y:longint;
begin
 i:=l;j:=r;
 x:=f2[(l+r)div 2];
 repeat
  while f2[i]<x do inc(i);
  while x<f2[j] do dec(j);
  if i<=j then
  begin
   y:=a[i];a[i]:=a[j];a[j]:=y;
   y:=b[i];b[i]:=b[j];b[j]:=y;
   y:=f1[i];f1[i]:=f1[j];f1[j]:=y;
   y:=f2[i];f2[i]:=f2[j];f2[j]:=y;
   inc(i);dec(j);
  end;
 until i>j;
 if l<j then sort(l,j);
 if i<r then sort(i,r);
end;
begin
 readln(n);
 for i:=1 to n do
 begin
  readln(st);
  a[i]:=(ord(st[1])-65)*26+ord(st[2])-64;//转换正整数
  b[i]:=(ord(st[pos(' ',st)+1])-65)*26+ord(st[pos(' ',st)+2])-64;//转换正整数
  f1[i]:=a[i]-b[i];//如题
  f2[i]:=a[i]*b[i];//如题
 end;
 sort(1,n);
 for i:=1 to n do
 begin
  if f2[i]>f2[i-1] then filldword(f,sizeof(f) div 4,0);
  if f1[i]=0 then continue;//不能算
  inc(ans,f[-f1[i]]);
  inc(f[f1[i]])
 end;
 writeln(ans);
end.

```

---

## 作者：LightningUZ (赞：1)

### 这是一个真的没有log的题解！！！

#### 中心思想

就是哈希法。但是由于长度太短，$26^4$，差不多$5e5$级别。所以不用取膜，而且珂以直接开数组存。对于一个省-市组合$(a[i],b[i])$，我们在$1$到$i-1$之间统计$(b[i],a[i])$的数量，累加起来，即珂。

#### 具体思维过程

显然（懒得证了），城市名字只有前两位有用。那么我们在读入的时候，就只把前两位保存下来即珂。

然后，如何更高效的存下来呢？由于只有大写字母，那我们当它是两位$26$进制数存下来就好了。

具体的说，假设第一位是$S[1]$，第二位是$S[2]$，那么我们把这个字符串存成$26(S[1]-'A')+(S[2]-'A')$（说白了就是哈希）。对于省和市的简称，我们都这样保存。省存在$a$数组里，市存在$b$数组里。

我们把$a[i]$和$b[i]$再哈希一遍，变成$676a[i]+b[i]$。（注：$676=26^2$），开数组存个数。设$cnt[S]$表示当前有多少个省-市组合的状态被表示为数字$S$。

对于第$i$个，满足条件的个数就是$cnt[676b[i]+a[i]]$了。然后记得记录$cnt[676a[i]+b[i]]++$。

#### 复杂度分析

时间复杂度：$O(n+|\Sigma|^4)$

空间复杂度：$O(|\Sigma|^4)$

（$\Sigma$是字符集。本题中，$\Sigma$=大写字母集，所以$|\Sigma|=26$，这个方法才能过）

#### 坑点

注意判掉$a[i]=b[i]$的情况，~~我去下载数据了~~，这种情况是不合法的！（还WA了一次...）

#### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace Flandre_Scarlet
{
    #define N 1666666 
    //开500000就行了
    //反正又不会TLE，不想那么多了
    #define int long long 
    //答案珂能会到n^2级别，记得开long long！
    #define F(i,l,r) for(int i=l;i<=r;++i)
    #define D(i,r,l) for(int i=r;i>=l;--i)
    #define Fs(i,l,r,c) for(int i=l;i<=r;c)
    #define Ds(i,r,l,c) for(int i=r;i>=l;c)
    #define MEM(x,a) memset(x,a,sizeof(x))
    #define FK(x) MEM(x,0)
    #define Tra(i,u) for(int i=G.Start(u),__v=G.To(i);~i;i=G.Next(i),__v=G.To(i))
    #define p_b push_back
    #define sz(a) ((int)a.size())
    #define iter(a,p) (a.begin()+p)
    void R1(int &x)
    {
        x=0;char c=getchar();int f=1;
        while(c<'0' or c>'9') f=(c=='-')?-1:1,c=getchar();
        while(c>='0' and c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
        x=(f==1)?x:-x;
    }
    void Rd(int cnt,...)
    {
        va_list args;
        va_start(args,cnt);
        F(i,1,cnt) 
        {
            int* x=va_arg(args,int*);R1(*x);
        }
        va_end(args);
    }

    int n;
    int a[N],b[N];
    char s1[N],s2[N];
    void Input()
    {
        R1(n);
        F(i,1,n)
        {
            scanf("%s%s",s1+1,s2+1);
            a[i]=(s1[1]-'A')*26+(s1[2]-'A');
            b[i]=(s2[1]-'A')*26+(s2[2]-'A');
            //读入的时候就变成数字表示
            //0<=a[i],b[i]<676
            //676=26^2
        }
    }

    int cnt[N];
    //和上面说的一样
    void Soviet()
    {
        int ans=0;
        F(i,1,n) 
        {
            if (a[i]==b[i]) continue;
            //坑！！！！！！！
            
            ans+=cnt[b[i]*676+a[i]]; //在前面找(b[i],a[i])
            cnt[a[i]*676+b[i]]++;
            //记录(a[i],b[i])
        }
        printf("%lld\n",ans);
    }

    #define Flan void
    Flan IsMyWife()
    {
        Input();
        Soviet();
    }
    #undef int //long long 
}
int main()
{
    Flandre_Scarlet::IsMyWife();
    getchar();getchar();
    return 0;
}
```

---

