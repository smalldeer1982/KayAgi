# Cinema

## 题目描述

莫斯科在举办一场重要的有$n$ 个不同国家的珂学家参与的国际会议，每个珂学家都只会一种语言。为了方便起见，我们规定一种语言用$1$ 到$10^9$ 的数来描述。 
在会议之后的晚上，珂学家们决定去看电影。他们去的电影院有$m$ 场电影，每场有两个不同的数字，分别代表配音的语言和字幕的语言。如果一个珂学家能听懂配音，他会非常愉悦；如果能看懂字幕，他会比较满意。如果既看不懂也听不懂，他会很生气。 
珂学家们决定去看同一场电影，你必须帮助他们选择一场电影，让愉悦的人最多的前提下，比较满意的人最多。

## 样例 #1

### 输入

```
3
2 3 2
2
3 2
2 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
6
6 3 1 1 3 7
5
1 2 3 4 5
2 3 4 5 1
```

### 输出

```
1
```

# 题解

## 作者：陷语 (赞：23)

### CF670C 【Cinema】

这道题我只用了sort，其它东西都是自己手写的，代码可读性应该比其他人高一点，希望这篇题解管理员可以通过。

先说一下我这道题的思路吧：

**1.因为这道题语言种类的范围是int，所以直接暴力统计是不行的，所以我们要将数据离散化一下，当然也可以map或者hash之类的，不过我感觉离散化不是太难，就直接写了个离散化。**

**2.将所有语言离散化后我们可以通过二分搜索直接去找每一个科学家会的语言，并开一个数组存下每种语言有几个人会。**

**3.分别搜索并计录配音语言和字幕语言，通过对比判断出选择哪一个才是最佳的选择。**

想这道题的思路其实并~~不难~~，我也就只WA了两遍（QAQ）
只要细节多注意一点过这道题还是不难的。

附上我的代码（**时间复杂度为O((n + m)log(n + m**）:
```cpp
#include <cstdio>
#include <algorithm>

using namespace std;
const int N = 400005;

int n, m;
int a[N], b[N], c[N], d[N + N / 2], e[N + N / 2], k[N];
int ans = 1, ans1, ans2;
//离散化 
inline void discrete(int x) {
    int t = 0;
    sort(d + 1, d + 1 + x);
    for(int i = 1; i <= x; ++i)
        if(i == 1 || d[i] != d[i - 1]) e[++t] = d[i];//去重+离散 
    e[0] = t;//将去重后的长度直接保存在e[0]里面。 
}
//二分搜索 
inline int query(int x) {
    
    int l = 1, r = e[0], mid;//自己写的二分 
    while(l < r) {
        mid = (l + r) >> 1;
        if(e[mid] >= x) r = mid;
        else l = mid + 1;
    }
    return l;
}

int main() {
//	freopen("in.txt", "r", stdin);
    int t = 0;
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        scanf("%d", a + i);
        d[++t] = a[i];
    }
    scanf("%d", &m);
    for(int i = 1; i <= m; ++i) {
        scanf("%d", b + i);
        d[++t] = b[i];
    }
    for(int i = 1; i <= m; ++i) {
        scanf("%d", c + i);
        d[++t] = c[i];
    }
    
    discrete(t);//把所有语言离散化一遍

    for(int i = 1; i <= n; ++i) k[query(a[i])]++;//暴力统计
    
    for(int i = 1; i <= m; ++i) {
        int x = k[query(b[i])], y = k[query(c[i])];
        if(x > ans1 || (x == ans1 && y > ans2)){//与上一个答案对比选出最佳 
            ans = i;
            ans1 = x;
            ans2 = y;//为了下一次比较，保存这一次答案 
        }
    }
    
    printf("%d\n", ans);
    return 0;
}
```



---

## 作者：Rye_Catcher (赞：11)

- 题目链接：
   
   https://www.luogu.org/problemnew/show/CF670C
   
- 思路：

  - step-1：
  
    语言的数据范围是10^9,所以我们采取用map离散化,这样就能方便且不MLE地记录每个语言会的人数。
  
  - step-2：
  
    然后我们再遍历一遍所有场次的电影,记录下最多人能听懂声音的那一场,放在一个ok数组里。
    
    接着再遍历ok数组,记录最多人能看懂字幕的那一场就是答案。
    
- Tips:

  - step-2能用sort代替，但实测这样会过不了第125个点，因为那个点数据比较毒瘤。下面的代码也给出了sort的cmp函数。
  - mx（最大值）要设成小于0的数,多亏了样例2,因为样例2中第一场电影的字幕没有一个人懂。
  
- 代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <cstring>
#include <algorithm>
#include <cctype>
using namespace std;
const int maxn=200005;
map <int,int> lan;
struct Film{
    int voi,tit,index;
}film[maxn];
int n,m;
template <class T>inline void read(T &x)
{
    x=0;char c;int ne=0;
    while(!isdigit(c=getchar()))ne=c=='-';
    x=c-48;
    while(isdigit(c=getchar()))x=(x<<3)+(x<<1)+c-48;
    x=ne?-x:x;
}
inline bool cmp(const Film &x,const Film &y)
{
    if(lan[x.voi]==lan[y.voi])
    {
        return lan[x.tit]>lan[y.tit];
    }
    return lan[x.voi]>lan[y.voi];
}
int main()
{
    int x,mx=-1;
    scanf("%d",&n);
    for(register int i=1;i<=n;i++){
        read(x);
        lan[x]++;
    }
    scanf("%d",&m);
    for(register int i=1;i<=m;i++){
        read(film[i].voi);
        film[i].index=i;
    }
    for(register int i=1;i<=m;i++){
        read(film[i].tit);
    }
    //sort(film+1,film+1+m,cmp);
    int ok[maxn],cnt=0,ans;  //step-2
    for(register int i=1;i<=m;i++){
        if(lan[film[i].voi]>mx){
            cnt=0,mx=lan[film[i].voi];
            ok[++cnt]=i;
        }
        else if(lan[film[i].voi]==mx){
            ok[++cnt]=i;
        }
    }mx=-1;
    for(register int i=1;i<=cnt;i++){
        if(lan[film[ok[i]].tit]>mx){
            mx=lan[film[ok[i]].tit];ans=ok[i];
        }
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：Ein_Niemand (赞：11)

### 看见大佬们一个个都用map，身为蒟蒻的我瑟瑟发抖，只好手打离散化~~~虽然时间有点慢~只跑了6000ms

我这里采取的是用vector进行离散化：

```cpp
vector<int>v;
```
v用来储存需要离散的数

------------------------
```cpp
read(a[i]),v.push_back(a[i]);
stable_sort(v.begin(),v.end());
```
读入并排序


------------------------
**很关键的一步操作↓↓↓**

```
v.erase(unique(v.begin(),v.end()),v.end());
```

------------------------

这里我来解释一下

unique()是C++标准库函数里面的函数，其功能是**去除**相邻的**重复元素**（只保留一个），所以使用前需要对数组进行**排序**（升序降序均可），具体使用如下：

对于长度为n数组a，unique(a+1,a+n+1)返回的是**迭代器**，迭代器指向的是**重复元素的首地址**

如果非要得到**不重元素的个数**，可以用 unique(a+1,a+n+1) -a - 1表示；

下面举个栗子：

比如这是去重前已排好序的数：

|  1|1  | 1 | 2 | 3 | 4 | 4 | 5 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |

那么unique一遍后，就会得到如下的数组：

|  1| 2 | 3 | 4 | 5 | 1 | 1 | 4 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |

从这里可以看出unique只是帮你**整理出不重复元素，重复的元素还是码放在后面**。

所以这是我们就要用到erase：

erase是vector自带的函数,即删除**a[v.begin()]~~a[v.end()-1]**；

------------------------

然后就可以写一个query函数找出某个数被离散化成了什么：

```cpp
int query(int x) {return lower_bound(v.begin(),v.end(),x)-v.begin()+1;}
```
------------------------

了解上述知识后就可以写出一个用vector进行离散化的模板了：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[10005],c[10005];
//c[]即储存离散化后的数 
vector<int>v;
inline int query(int x){return lower_bound(v.begin(),v.end(),x)-v.begin()+1;}
int main()
{
	scanf("%d",&n);
	for(register int i=1;i<=n;++i) 
    	scanf("%d",&a[i]),v.push_back(a[i]);
	stable_sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());
	for(int i=1;i<=n;++i) c[i]=query(a[i]);
}
```

------------------------

那么关于这道题，我的思路是：

### 1. m部电影和n个**珂学家**最多有**(m*2+n)种语言**，我们把所有涉及的语言push到v里面，排序并进行离散化，

### 2. 然后开个**2∗m+n**的数组去统计每个人会的语言， 

### 3. 最后枚举每个电影判断.


下面就是大家最喜欢的高清无码的代码时间了。

------------------------

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<climits>
#include<bitset>
#include<vector>
using namespace std;
#define R register int
#define LL long long
#define db double
#define I inline int
#define V inline void
const int maxn=200005;
#define F1(i,a,b) for(R i=a;i<=b;++i)
#define F2(i,a,b) for(R i=a;i>=b;--i)
#define F3(i,a,b,c) for(R i=a;i<=b;i+=c)
#define F4(i,a,b,c) for(R i=a;i>=b;i-=c)
#define min(x,y) x<y?x:y
#define max(x,y) x>y?x:y
V read(R &x)
{
	R f=1;x=0;register char c=getchar();
	for(;c>'9'||c<'0';c=getchar()) if(c=='-') f=-1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<3)+(x<<1)+(c^48);
	x*=f;
}
V print(R x)
{
	if(x<0) x=-x,putchar('-');
	if(x>9) print(x/10);
	putchar(x%10+'0');
}
int a[maxn],s[maxn],n,t,index[maxn*3],m,r[maxn],maxx=-1,maxy=-1,ans=1;

//a[]表示电影语言，s[]表示电影字幕，r[]为人的语言，maxx是最多有几个人听得懂，maxy表示有几个人看得懂

//因为我害怕有没有人能听懂或看懂这样的数据，所以就把ans初值置为1
vector<int>v;
I query(R x) {return lower_bound(v.begin(),v.end(),x)-v.begin()+1;}
int main()
{
	read(n);
	F1(i,1,n) read(r[i]),v.push_back(r[i]);
	read(m);
	F1(i,1,m) read(a[i]),v.push_back(a[i]);
	F1(i,1,m) read(s[i]),v.push_back(s[i]);
	stable_sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());
	F1(i,1,n) t=query(r[i]),++index[t];
	F1(i,1,m)
	{
		R x=query(a[i]),y=query(s[i]);
		if(index[x]>maxx)
			maxx=index[x],maxy=index[y],ans=i;
        //如果两部电影能听懂的人一样多，就比较能看懂字幕的人的多少
		else if(index[x]==maxx&&index[y]>maxy)
			maxy=index[y],ans=i;
	}
	print(ans);
	return 0;
}
```

---

## 作者：Kizuna_AI (赞：5)

## 广告：[我的博客](https://blog.likecoding.ooo)
## 给大家讲个笑话，这道题有138个测试点
貌似没有用struct+sort一起排序的。那么我就讲讲我自己的代码。  
我的第一反应就是这道题需要排序，那么我们注意到这个$a_i$,$b_i$,$c_i$他的数据范围是$10^9$。所以需要进行离散化。然而我太菜了，所以使用了map来代替离散化。  
总体思路如下：  
1. 输入$a_i$的时候，我们记录会$a_i$语言的人有多少 `ma[a[i]]++;`  
2. 然后，我们查看$b_i$有多少人会听懂配音用的语言`t[i].t1=ma[b[i]];`
3. 同理，我们也要统计$c_i$有多少人会看懂字幕用的语言 `t[i].t2=ma[c[i]];`
4. 我们对此进行排序，查看哪个电影最受他们满意，也就是这一段代码。 
```
bool cmp(const language &x,const language &y) {
	return x.t1>y.t1 || x.t1==y.t1 && x.t2>y.t2;
}
```
如果大家对这个代码看的不是特别懂的话，可以尝试这段更好理解的代码
```
bool cmp(const language &x,const language &y) {
	if(x.t1>y.t1) return true;
   if(x.t1<t.t1) return false; //这里不能直接使用else，直接使用else会导
   			             //致x.t1==y.t1情况也会直接被return false
   			             //，而不能被考虑到字幕用的语言
   //这个时候就只剩x.t1==y.t1的情况了，在配音用的语言相同的情况下在考虑字幕用的语言
   if(x.t2>y.t2) return true;
   else return false; //只有这个时候才可能使用else哦
}
```
5. 那么排完序第一个就是最受欢迎的电影

记录ID的原因：排序过后他们的下标就会改变，所以需要记录原来的下标，最后才能输出

贴上代码：
```
#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[200010],b[200010],c[200010];
int f[200010];
struct language {
	int t1,t2,id;
};language t[200100];
map<int,int> ma;
bool cmp(const language &x,const language &y) {
	return x.t1>y.t1 || x.t1==y.t1 && x.t2>y.t2;
}
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		ma[a[i]]++;
	}
	scanf("%d",&m);
	for(int i=1;i<=m;i++) {
		scanf("%d",&b[i]);
		t[i].t1=ma[b[i]];
		t[i].id=i;
	}
	for(int i=1;i<=m;i++) {
		scanf("%d",&c[i]);
		t[i].t2=ma[c[i]];
	}
	sort(t+1,t+1+m,cmp);
	printf("%d",t[1].id);
	return 0;
}
```
可能有些人对map的具体使用方法可能不是特别了解。不了解的可以去参考一下三个网站
1. [cppreference](https://zh.cppreference.com/w/cpp/container/map)
2. [oi-wiki](https://oi-wiki.org/ds/stl/map/)
3. [cplusplus官网（英文）](http://www.cplusplus.com/reference/map/map/?kw=map)

---

## 作者：浮云启心 (赞：5)

先把语言排序，对于每个电影的语音和字幕分别进行二分计算人数，然后就是比大小，答案初始化为1，避免出现0的情况。

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <string>
int a[200002],b[2000002];

int inline read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int main()
{
    int n;
    std::cin>>n;
    for(int i=1;i<=n;i++)a[i]=read();
    
    std::sort(a+1,a+1+n);
    int m;
    std::cin>>m;
    for(int i=1;i<=m;i++)b[i]=read();
    int gg=0,hh=0,ff=1,v;
    for(int i=1;i<=m;i++)
    {
        v=read();
        
        int k1=(int)(std::upper_bound(a+1,a+1+n,b[i])-a)-(int)(std::lower_bound(a+1,a+1+n,b[i])-a);
        
        int k2=(int)(std::upper_bound(a+1,a+1+n,v)-a)-(int)(std::lower_bound(a+1,a+1+n,v)-a);
        if(k1>gg||(k1==gg&&k2>hh))gg=k1,hh=k2,ff=i;
    }
    
    std::cout<<ff<<std::endl;
}
```

---

## 作者：NuoCarter (赞：4)

可以很快地想到一个暴力做法：

开一个 1e9 的桶 $t_i$

使用一个结构体储存两个关键字：

一个是 second = 字幕可以看懂的人数

一个是 first = 电影本身可以看懂的人数

每次输入的 $b_i$ 与 $c_i$

$first=t_{b_i}$

$second = t_{c_i}$

最后再按两个关键字排序就可以了。。

但是 1e9 的桶会 MLE

所以不用桶，用一个 map 映射就可以了吧

Code:
``` cpp
#include<bits/stdc++.h>
using namespace std;
const int MAX = 200010;
int n,mm;
map<int, int> m;
struct node {
    int pos,first,second;
}a[MAX];
inline bool cmp(node x,node y){
	if(x.first!=y.first)	return x.first>y.first;
	return x.second>y.second;	
}
int main(){
    scanf("%d",&n);
    int x;
    for(int i = 1;i <= n;++i){
        int x;
        scanf("%d",&x);
        m[x]++;
    }
    scanf("%d",&mm);
    for(int i = 1;i <= mm;++i){
        scanf("%d",&x);
        a[i].pos = i,a[i].first = m[x];
    }
    for(int i = 1;i <= mm;++i){
        scanf("%d",&x);
        a[i].second = m[x];
    }
    sort(a+1,a+mm+1,cmp);
    printf("%d\n",a[1].pos);
    return 0;
}


```

---

## 作者：小小小朋友 (赞：4)

**题意描述**：有许多电影和珂学家，电影有字幕和音频，珂学家听的懂音频满意，看得懂字幕为较满意，求最多满意的人，但语言的数非常大……

**思路**：哈希统计（可用STL map）STL大法好！！

吐槽：数据居然会卡死unordered_map！

**代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
unordered_map<int,int> m1;//统计用映射
int n,m,a[N],b[N],c[N],ans=-1;//ans 记录答案下标
int main(){
	cin>>n;
	for(int i=0;i<n;i++) cin>>a[i],m1[a[i]]++;//统计珂学家 
	cin>>m;
	for(int i=0;i<m;i++) cin>>b[i];
	for(int i=0;i<m;i++) cin>>c[i];
	ans=0;
	for(int i=0;i<m;i++){
		if(m1[b[i]]>m1[b[ans]]) ans=i;
		else if(m1[b[i]]==m1[b[ans]]&&m1[c[i]]>m1[c[ans]]) ans=i;
	}
	cout<<ans+1;//因为是下标，所以要加一
	return 0;
}
```

---

## 作者：Wall_breaker (赞：3)

~~刷lyd大佬题目看见了这道题，结果调了20min，我太菜了~~

我们来看一看这道题。

##### （感谢Acwing的良心翻译）

莫斯科正在举办一个大型国际会议，有n个来自不同国家的科学家参会。

每个科学家都只懂得一种语言。

为了方便起见，我们把世界上的所有语言用1到10^9之间的整数编号。

在会议结束后，所有的科学家决定一起去看场电影放松一下。

他们去的电影院里一共有m部电影正在上映，每部电影的语音和字幕都采用不同的语言。

对于观影的科学家来说，如果能听懂电影的语音，他就会很开心；如果能看懂字幕，他就会比较开心；如果全都不懂，他就会不开心。

现在科学家们决定大家看同一场电影。

请你帮忙选择一部电影，可以让观影很开心的人最多。

如果有多部电影满足条件，则在这些电影中挑选观影比较开心的人最多的那一部。


------------

好的，我们看完了题，来看一看核心思想。

### 核心：离散化去重

为什么要离散化呢？题面上讲了，原数在int范围内，hash数组肯定是开不下的，所以我们来一发离散化。

简单来说，就是把出现的较大的数去掉重复的数后给它们一个比较小的新的编号，然后在hash判断。

```
inline void discrete() {
	len = 0;
	int l = 0;
	for (int i = 1; i <= n; i ++) {
		d[++ l] = a[i];
	}
	for (int i = 1; i <= m; i ++) {
		d[++ l] = b[i];	
	}
	for (int i = 1; i <= m; i ++) {
		d[++ l] = c[i];
	}
	sort(d + 1, d + l + 1);
	for (int i = 1; i <= l; i ++) if (d[i] != d[i - 1]) e[++ len] = d[i];//去重+排序
}
inline int query(int x) {
	return lower_bound(e + 1, e + len + 1, x) - e; //查询x在e数组中的位置，作为x的新编号
}
```

离散化完后怎么选择电影呢？

我们把科学家们的语言全部hash进vis数组中。然后遍历电影，判断声音和字幕符合的个数，找到声音个数最大的某个电影，使它在同样声音个数的电影中字幕个数最大就行了。

上代码（送一发快读）：
```
#include<bits/stdc++.h>
using namespace std;
template <typename T>
inline void read(T &x) {
	x = 0;
	T f = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') f = -1;
	for (; isdigit(c); c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
	x *= f;
}
inline void d_read(double &x) {
	x = 0.0;
	int f = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') f = -1;
	for (; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
	if (c == '.'){
		double num = 1.0;
		c = getchar();
		for (; isdigit(c); c = getchar()) x = x + (num /= 10) * (c ^ 48);
	}
	x *= f;
}

template <typename T>
inline void w(T x) {
	if (x > 9) w(x / 10);
	putchar(x % 10 + 48);
}
template <typename T>
inline void write(T x, char c) {
	if (x < 0){
		putchar('-');
		x = -x;
	}
	w(x);
	putchar(c);
}
int len, n, m, a[200005], b[200005], c[200005], d[600005], e[600005], vis[1000005];
inline void discrete() {
	len = 0;
	int l = 0;
	for (int i = 1; i <= n; i ++) {
		d[++ l] = a[i];
	}
	for (int i = 1; i <= m; i ++) {
		d[++ l] = b[i];	
	}
	for (int i = 1; i <= m; i ++) {
		d[++ l] = c[i];
	}
	sort(d + 1, d + l + 1);
	for (int i = 1; i <= l; i ++) if (d[i] != d[i - 1]) e[++ len] = d[i];
}
inline int query(int x) {
	return lower_bound(e + 1, e + len + 1, x) - e;
}
int main(){
	read(n);
	for (int i = 1; i <= n; i ++) {
		read(a[i]);
	}
	read(m);
	for (int i = 1; i <= m; i ++) read(b[i]);
	for (int i = 1; i <= m; i ++) read(c[i]);
	discrete();
	for (int i = 1; i <= n; i ++) {
		int u = query(a[i]);
		vis[u] ++;
	}
	int tot = 0, cnt = 0;
	int ans = 1;
	for (int i = 1; i <= m; i ++) {
		int u = query(b[i]), v = query(c[i]);
		if (vis[u] > tot || vis[u] == tot && vis[v] > cnt) {
			tot = vis[u];
			ans = i;
			cnt = vis[v];
		}
	}
	write(ans, '\n');
	return 0;
}
```

---

## 作者：Energy_Making (赞：2)

# **前置知识**：离散化或[map](https://oi-wiki.org/lang/csl/associative-container/#map)
先读题，读完题目后本能想到用桶来做，没读入一名科学家的语言i就将$tong_i$加1，最后将电影的开心人数存到结构体中，在排序便好。但是有1e9种语言，数组肯定存不下。但是 $1 \le n,m \le 200000$，所以只需要用**离散化**来优化即可。但奈何蒟蒻太弱，不会写离散化，便用了map来做。
# 能让XXSAC此题的东西
```cpp
#include<stdio.h>
#include<bits/stdc++.h>
#define ll long long//其实并不需要开long long
using namespace std;
int n,m;
struct node
{
	int more,most;
	ll ID;//最后输出编号，故存储下标。
};
node poi[200005];
bool cmp(node a,node b)//结构体排序常规操作。
{
	if(a.most==b.most)return a.more>b.more;
	return a.most>b.most;
}
map<ll,int> mp;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int a;//节省空间，从我做起。
		scanf("%d",&a);
		mp[a]++;
	}
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		int b;
		scanf("%d",&b);
		poi[i].most=mp[b];
		poi[i].ID=i;
	}
	for(int i=1;i<=m;i++)
	{
		int c;
		scanf("%d",&c);
		poi[i].more=mp[c];
	}
	sort(poi+1,poi+1+m,cmp);
	printf("%lld",poi[1].ID);// 从大到小排序，故输出第一项。
	return 0;
}
```


---

## 作者：pitiless0514 (赞：2)

## CF670C 【Cinema】
### 思路：
这一题是一道很简单的排序题，蓝书上面都有，思路就是，看到这道题，大家肯定和我一样都想到了用桶将每个人语言会的语言给存起来，因为$n,m$小于$200000$,所以暴力扫一遍是不会超时的，但是$a[i]$最大可能达到$10^9$,那么你用桶是开不下的，这是我们就会想到一个好东西——**离散化**。

#### 离散化是啥？

>离散化，就是把无限空间中有限的个体映射到有限的空间中去，以此提高算法的时空效率。
通俗的说，离散化是在不改变数据相对大小的条件下，对数据进行相应的缩小。

那么接下来，$n$个人，**每个人会一种语言**，$m$场电影，**最坏情况下，就是$n+2*m$种语言**,那么直接开一个大小为$n+2*m$大小的数组记录我们排序并离散化后的数，然后用桶扫一遍，不过对于条件先判断听懂的人，再判断看懂文字的人，顺便初始答案直接为1，接下来就直接上代码。
## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,vis[600009],a[600009],f,b[600009],c[600009],m,t,d[600009],e[600009];
void pre(){
	sort(d,d+t+1);
	for(int i=1;i<=t;i++){
		if(i==1||d[i]!=d[i-1]){
			e[++f]=d[i];
		}
	}
}//离散化
int query(int x){
	return lower_bound(e+1,e+f+1,x)-e;//二分查找函数
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		d[++t]=a[i];
	} 
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		scanf("%d",&b[i]);
		d[++t]=b[i];
	}
	for(int i=1;i<=m;i++){
		scanf("%d",&c[i]);
		d[++t]=c[i];
	}
	pre();
	for(int i=1;i<=n;i++){
		vis[query(a[i])]++;//桶统计
	}
	int ans=0,k=1,now=0;
	for(int i=1;i<=m;i++){
		int r=query(b[i]);
		int rt=query(c[i]);
	//	printf("%d %d\n",vis[r],vis[rt]);
		if(vis[r]>=ans){
			if(vis[r]==ans){
				if(vis[rt]>now){
					now=vis[rt];
					ans=vis[r];
					k=i;
				}
			}
			else{
				now=vis[rt];
				ans=vis[r];
				k=i;
			}
		}
	}
	printf("%d\n",k);
	return 0;
}
```




---

## 作者：John_yangliwu (赞：1)

# 思路
因为语言的编号值域很大，直接统计不是爆时间就是爆空间。但注意到最多只有 $4\times10^5$ 种语言，所以考虑离散化，将编号映射到 $1$ 至 $4\times10^5$ 上。

离散化后，对于每部电影：
1. 统计非常愉悦的人数，记为 $x$；
2. 统计比较满意的人数，记为 $y$；
3. 用 $x,y$ 更新答案。

# 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 400005;

int a[MAXN], b[MAXN], c[MAXN];
int all[2 * MAXN];
int e[2 * MAXN];
int cnt[2 * MAXN];
int n, m;
int len = 0;
int id = 1, ans0, ans1;

void discrete(int t) { //离散化
    sort(all + 1, all + 1 + t);
    for(int i = 1; i <= t; i++) {
        if(i == 1 || all[i] != all[i - 1]) e[++len] = all[i];
    }
}

int query(int x) { //查询 x 映射为哪个整数
    //相当于二分查找 x
    return lower_bound(e + 1, e + 1 + len, x) - e;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int t = 0;

    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        all[++t] = a[i];
    }
    cin >> m;
    for(int i = 1; i <= m; i++) {
        cin >> b[i];
        all[++t] = b[i];
    }
    for(int i = 1; i <= m; i++) {
        cin >> c[i];
        all[++t] = c[i];
    }

    discrete(t);
    for(int i = 1; i <= n; i++)
    	cnt[query(a[i])]++; //cnt 统计懂得每种语言的人数

    for(int i = 1; i <= m; i++) {  
        int x = cnt[query(b[i])], y = cnt[query(c[i])];
        if(x > ans0 || (x == ans0 && y > ans1)) {
            id = i; ans0 = x; ans1 = y;
        }
    }

    cout << id << endl;
    return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/52371091)

---
$\large\text{THE\ \ \ END}$

---

## 作者：Soledad_S (赞：1)

退役前发文了。

排序和离散都是稳定的一只$log$的做法，这里给大家介绍一种玄学复杂度的数据结构，$hash$表。

$hash$表的思想很简单，**将所有对$mod$取模在一个同余类的数用链表串起来** ~~（不要告诉我你不会链表）~~，这样时间复杂度就依赖于$mod$大小。**理论上来说**，$mod$越大，同余类的冲突越小，跑得就快些；$mod$越小，每个同余类里聚集的数较多，跑得就慢些。我们往往需要找到那个空间和时间上的平衡点。

经实测，本题的较优$mod$是$1e6$，还有一个小优化，就是对于小于$mod$的数，单独开桶来记，但影响不大。

解决了本题的瓶颈，其他地方就不细讲了。

本题解卡了下常，[拿到了$rank 1$](https://www.luogu.org/record/24901296)（但估计很快就死了QwQ），[$rank 2$是我们机房的一个奆奆](https://www.luogu.org/record/24901493)，他的$mod$是$1e6+7$，但没有加那个小优化。

```cpp
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define INF 0x3f3f3f3f
inline char gc(){
	static char buf[100000],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
	char ch;
	int bj=1;
	while(!isdigit(ch=gc()))
	  bj=(ch=='-')?-1:1;
	int res=ch^(3<<4);
	while(isdigit(ch=gc()))
	  res=(res<<1)+(res<<3)+(ch^(3<<4));
	return res*bj;
}
void printnum(int x){
	if(x>9)printnum(x/10);
	putchar(x%10+'0');
}
inline void print(int x,char ch){
	if(x<0){
		putchar('-');
		x=-x;
	}
	printnum(x);
	putchar(ch);
}
const int mod=1e6;
int to[200000],v[200000],nxt[200000],h[mod],cnt;
int n,m,a[200005],b[200005],t[mod];
int maxn1=-INF,maxn2=-INF,ans;
inline void Insert(int x){
	if(x<mod){
		t[x]++;
		return;
	}
	for(int i=h[x%mod];i;i=nxt[i])
		if(to[i]==x){
			v[i]++;
			return;
		} 
	to[++cnt]=x;
	v[cnt]=1;
	nxt[cnt]=h[x%mod];
	h[x%mod]=cnt;
}
inline int query(int x){
	if(x<mod)return t[x];
	for(int i=h[x%mod];i;i=nxt[i])
		if(to[i]==x)return v[i];
	return 0;
}
signed main(){
	n=read();
	int x;
	while(n--)x=read(),Insert(x);
	m=read();
	for(int i=1;i<=m;i++)a[i]=read();
	for(int i=1;i<=m;i++)b[i]=read();
	for(int i=1;i<=m;i++){
		int tmp1=query(a[i]),tmp2=query(b[i]);
		if(tmp1>maxn1){
			maxn1=tmp1;
			maxn2=tmp2;
			ans=i;
		}
		else if(tmp1==maxn1&&tmp2>maxn2){
			maxn1=tmp1;
			maxn2=tmp2;
			ans=i;
		}
	}
	print(ans,'\n');
	return 0;
}

```


---

## 作者：Llf0703 (赞：1)

推广博客：https://llf0703.com/p/cf-670c.html

**不需要用离散化**的朴素排序做法。

## 题意

从 $m$ 部电影中选出 $1$ 部给 $n$ 个人看。每部电影的配音和字幕都使用的不同的语言，每个人只掌握一种语言，用 $1\le id\le 10^{9}$ 的数表示不同语言。

对于选出来的电影，如果某人能听懂配音，他会非常高兴；如果能看懂字幕，他会比较高兴。问：选择哪部电影，使得非常高兴的人最多；如果一样多，应使比较高兴的人最多。

$n,m\le 200000$ 。

## 题解

显然可以对每部电影分别计算出两个属性，最后取最大即可。

不同的人掌握的语言可能相同，那么可以把相同语言的人合并，记录语言和人数在数组 $\text{s[]}$ 中。

然后将两个属性分开考虑，先考虑配音。将配音的语言和所有人掌握的语言从小到大排序，可以在 $O(n+m)$ 下很容易的得到非常高兴的人的个数。字幕同理。

具体的实现是对电影的两个属性，用结构体 $(id,lan,ans)$ 表示`电影的序号`、`语言`和`非常高兴/较高兴`的人数。对于观众，~~我懒得再开结构体~~，用 $(id,lan)$ 表示`语言`和`人数`。

```cpp
#include<bits/stdc++.h>

using namespace std;

inline int read()
{
    char ch=getchar();
    int f=1,x=0;
    while (ch<'0' || ch>'9')
    {
        if (ch=='-') f=-1;
        ch=getchar();
    }
    while (ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return f*x;
}

int n,m,a[200005];
struct node {
    int id,lan,ans;
} b[200005],c[200005],s[200005];

inline bool cmp(node x,node y) { return x.lan<y.lan; } //按语言排序

inline bool cmp2(node x,node y) { return x.id<y.id; } //按序号排序，方便统计答案

signed main()
{
    n=read();
    for (int i=1;i<=n;i++) a[i]=read();
    sort(a+1,a+n+1);
    int cnt=1;
    s[1].id=a[1]; s[1].lan=1;
    for (int i=2;i<=n;i++)
    {
        if (a[i]==a[i-1]) s[cnt].lan++;
        else s[++cnt].id=a[i],s[cnt].lan=1;
    } //合并相同语言的人
    n=cnt;
    m=read();
    for (int i=1;i<=m;i++) b[i].lan=read(),b[i].id=i;
    for (int i=1;i<=m;i++) c[i].lan=read(),c[i].id=i;
    sort(b+1,b+m+1,cmp);
    sort(c+1,c+m+1,cmp);
    int j=1;
    for (int i=1;i<=m;i++) //处理配音
    {
        while (s[j].id<b[i].lan) j++;
        if (s[j].id==b[i].lan) b[i].ans+=s[j].lan;
    }
    j=1;
    for (int i=1;i<=m;i++) //处理字幕
    {
        while (s[j].id<c[i].lan) j++;
        if (s[j].id==c[i].lan) c[i].ans+=s[j].lan;
    }
    sort(b+1,b+m+1,cmp2);
    sort(c+1,c+m+1,cmp2); //按序号还原原来的顺序
    int ans=1;
    for (int i=2;i<=m;i++)
    {
        if (b[i].ans<b[ans].ans) continue;
        if (b[i].ans>b[ans].ans) ans=i; //非常高兴的人较多
        else if (c[i].ans>c[ans].ans) ans=i; //非常高兴的人相同，较高兴的人较多
    }
    return !printf("%d",ans);
}
```

---

## 作者：SegTre (赞：0)

$\quad$思路比较直接，先把每种语言使用人数统计出来，再以“非常愉悦”为第一关键字，“比较愉悦”为第二关键字，找出符合条件的电影。

注意以下几点：
- 语言种类达 $10^9$ 种，需要离散化处理。
- 电影的配音或字幕可能所有科学家都不懂，所以要初始化答案为第一部电影。
- $\operatorname{lowerbound}$ 函数会返回第一个大于等于要找的数的位置，就是说，即使数组中没有该数也能返回一个值，因此需要特判。

代码注释比较详细，直接上代码（附另一样例）。

```cpp
#include<cstdio>
#include<cctype>
#include<algorithm>
using namespace std;
inline int read() {
	int res;char c;
	while(!isdigit(c=getchar()));res=c^48;
	while(isdigit(c=getchar())) res=(res<<3)+(res<<1)+(c^48);
	return res;
}
int a[200005],b[200005],c[200005],cnt[200005],tot=1; // a,b,c意义如题，tot表示语言总数，cnt存每种语言使用人数 
int main() {
	int n=read(),m,x,y,ans=1,rec=1,maxn=0,maxm=0;//maxn记录第一关键字，maxm记录第二关键字 
	for(int i=1;i<=n;++i) a[i]=read();
	sort(a+1,a+n+1);
	for(int i=1;i<=n;++i) { //统计每种语言使用人数 
		if(a[i]!=a[rec]) {
			rec=i;
			tot++;
		}
		cnt[tot]++;
	}
	unique(a+1,a+n+1); //去重 
	m=read();
	for(int i=1;i<=m;++i) b[i]=read();
	for(int i=1;i<=m;++i) c[i]=read();
	for(int i=1;i<=m;++i) {
		x=lower_bound(a+1,a+tot+1,b[i])-a; 
		y=lower_bound(a+1,a+tot+1,c[i])-a;
		if(a[x]!=b[i]) x=0; //需要特判语言没人使用的情况 
		if(a[y]!=c[i]) y=0;
		if(cnt[x]>maxn) {
			maxn=cnt[x];
			maxm=cnt[y];
			ans=i;
		}
		else if(cnt[x]==maxn&&cnt[y]>maxm) {
			maxm=cnt[y];
			ans=i;
		}
	}
	printf("%d",ans);
	return 0;
}
  
/*
样例： 
20
2 2 1 6 6 5 10 2 5 5 4 8 6 8 8 10 2 1 5 6
20
1 9 1 1 5 1 9 10 1 10 9 9 8 7 5 1 1 10 2 7
3 5 9 10 10 8 2 9 6 7 8 8 6 5 3 4 6 3 7 4
答案：
5
*/
```


---

## 作者：_jimmywang_ (赞：0)

### 写题解写题解

------------

其实这题题意好理解，但是一看不知道咋做对不对？

### $Step 1:$普通想法$:$
可以这样：弄一个数组$t[i]$表示有几个人会第$i$种语言，然后对于每场电影$j$的语言$a$,$b$，求出$t[a]$和$t[b]$,然后开一个$ans$就万事大吉了。

代码长这样（别急着抄，都有“普通想法”四个字了，绝对没过）：

```
#include<algorithm>
#include<bitset>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<map>
#include<iostream>
#include<queue>
#include<set>
#include<stack>
#include<string>
#include<vector>
using namespace std;
#define ll long long
#define f(i,a,b) for(int i=a;i<=b;i++)
inline ll rr() {
	ll x=0,f=1;
	char c=getchar();
	if(c=='-')f=-1,c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return x*f;
}
#define d rr()
ll pe[1000010];
ll n,m;
struct mo{
	ll a,b;
}mo[1000010];
ll t[1000010];
ll xx,yy,mx=1;
int main(){
	n=d;
	f(i,1,n)pe[i]=d,t[pe[i]]++;
	m=d;
	f(i,1,m)mo[i].a=d;
	f(i,1,m)mo[i].b=d;
	f(i,1,m){
		ll x=mo[i].a;
		ll y=mo[i].b;
		ll xk=t[x];
		ll yk=t[y];
		if(xk>xx||(xk==xx&&yk>yy))xx=xk,yy=yk,mx=i;
	}
	cout<<mx;
	return 0;
}

```

那么是为什么呢？

原因很简单:题目说了，语言的编号在$int$范围内。

那怎么受得了？？

你有本事开一个$t[1000000001]$啊，保证不会$MLE$死你

### $Step 2:$离散化$:$

```
离散化，把无限空间中有限的个体映射到有限的空间中去，以此提高算法的时空效率。
通俗的说，离散化是在不改变数据相对大小的条件下，对数据进行相应的缩小。
	----百度百科
```
刚好适合本题呢~~

直接上代码吧，离散化这个东西嘛，就是$unique$啊，把一大堆很大的数弄成对应的小一点的数，类似$map$的映射。

```
#include<algorithm>
#include<bitset>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<map>
#include<iostream>
#include<queue>
#include<set>
#include<stack>
#include<string>
#include<vector>
using namespace std;
#define ll long long
#define f(i,a,b) for(int i=a;i<=b;i++)
inline ll rr() {
	ll x=0,f=1;
	char c=getchar();
	if(c=='-')f=-1,c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return x*f;
}
#define d rr()
ll lan[1000010];
ll pe[1000010];
ll bb[1000010];
ll n,m;
ll tot,num;
void disc(){
	sort(lan+1,lan+tot+1);
	f(i,1,tot)
		if(i==1||lan[i]!=lan[i-1])bb[++num]=lan[i];
}
ll k(ll x){
	return lower_bound(bb+1,bb+num+1,x)-bb;
}
struct mo{
	ll a,b;
}mo[1000010];
ll t[1000010];
ll xx=-1,yy=-1,mx=1;
int main(){
	n=d;
	f(i,1,n){
		ll x=d;
		lan[++tot]=x;
		pe[i]=x;
	}
	m=d;
	f(i,1,m){
		ll x=d;
		lan[++tot]=x;
		mo[i].a=x;
	}
	f(i,1,m){
		ll x=d;
		lan[++tot]=x;
		mo[i].b=x;
	}
	disc();
	f(i,1,n)
		t[k(pe[i])]++;
	f(i,1,m){
		ll x=mo[i].a;
		ll y=mo[i].b;
		ll xk=t[k(x)];
		ll yk=t[k(y)];
		if(xk>xx||(xk==xx&&yk>yy))xx=xk,yy=yk,mx=i;
	}
	cout<<mx;
	return 0;
}

```
完结撒花！！！

---

## 作者：hovny (赞：0)

## 题面

### [传送门](https://www.luogu.org/problemnew/show/CF670C)

## 思路：

### **离散化**、**hash**

对于这样一个明显的统计排序的题目，当然轻而易举啦~

但是！看！语言的编号 **a**数组和 **b**数组的值最大在$10^9$的级别，所以开个数组来存———That's impossible!

所以我们可以用上**离散化**（也就是hash）

离散化，我们有两种写法

#### 第一种是自己手码代码

先排序，然后去重，接着用二分一一对应，达到离散化的目的

板子：
```cpp
sort(b+1,b+n+1,cmp);
n=unique(b+1,b+n+1)-b-1
for(i=1;i<=n;i++)
	a[i]=lower_bound(b+1,b+n+1,a[i])-b;
```
#### 第二种是使用STL库的map

头文件：`#include <map>`

定义方式：`map<type,type> p;`表示将前一种type映射到后一种type

其中的类型可以很多，比如double，string，int，bool等基本类型，也包括pair这种

如`map<pair<int,int>,bool>p;`允许的

操作：一般用数组的形式，直接`p[x]`访问、写入

**PS**：但是map的速度比较慢，想进一步提高可以使用unordered_map

此处不才不做讲解，具体详见[洛谷日报](https://www.luogu.org/blog/yihan/unordered)

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int b;
int a[200010];
map<int,int> p;
int cur,res,ans;
int read()
{
	int s=0;
	char c=getchar();
	while(!isdigit(c))
		c=getchar();
	while(isdigit(c))
	{
		s=(s<<1)+(s<<3)+c-'0';
		c=getchar();
	}
	return s;
}
int main()
{
	int i;
	int x;
	n=read();
	for(i=1;i<=n;i++)
		p[read()]++;//科（珂）学家们能听懂的语言
	m=read();
	for(i=1;i<=m;i++)//电影配音
		a[i]=read();
	b=p[read()];
	ans=1;//一开始默认第一种是答案
	res=p[a[1]];
	cur=b;
	for(i=2;i<=m;i++)
	{
		b=p[read()];
		x=p[a[i]];
		if(x>=res)//比较听的懂配音，看的懂字幕的人数
		{
			if(x>res)
			{
				res=x;
				cur=b;
				ans=i;
			}
			else
				if(cur<b)
				{
					ans=i;
					cur=b;
				}
		}
	}
	printf("%d",ans);//跑过138个点！人憔悴！
	return 0;
}
```

### 推荐题目：

[「Luogu」[NOI2015]程序自动分析](https://www.luogu.org/problemnew/show/P1955)



---

## 作者：zhlgzhh (赞：0)

先用map统计每种语言有多少科学家会，然后遍历每场电影，找到愉悦人数最多前提下，满足人数最多的电影。
```cpp
#include <cstdio>
#include <map>
using namespace std;

int N,M,mova[200005],movs[200005];
map<int,int> lang;

int read()
{
	int r=0;
	char ch=getchar();
	while(ch<'0' || ch>'9')ch=getchar();
	while(ch>='0' && ch<='9')r=r*10+ch-'0',ch=getchar();
	return r;
}

int main()
{
	N=read();
	for(int i=1;i<=N;i++)lang[read()]+=1;
	M=read();
	for(int i=1;i<=M;i++)mova[i]=read();
	for(int i=1;i<=M;i++)movs[i]=read();
	
	//bestI-目前最佳电影（要初始化为1） 
	//bestP-目前最多几人愉悦
	//bestS-目前最多几人满意 
	int bestI=1,bestP=0,bestS=0;
	for(int i=1;i<=M;i++)
	{
		int a=lang[mova[i]],s=lang[movs[i]];
		if(a==bestP && s>bestS)bestI=i,bestS=s;
		else if(a>bestP)bestI=i,bestP=a,bestS=s;
	}
	printf("%d",bestI);
}
```

---

