# Wrath

## 题目描述

那手上流着无辜之人的血的罪人啊！

有n个罪犯排成一排，其中第i个人拿着一个长 $L_{i}$  的爪子。铃声敲响时每个人都会将其前面的一些人杀掉。所有人在同一时刻杀掉其他人。也就是说，如果$j<i$ 并且$j>=i-L_{i}$ ，那么第i个人将会杀掉第$j$ 个人。

现在给出每个爪子的长度，你要找出铃响之后还有多少人幸存。

## 说明/提示

第一个样例中，最后一个人杀掉他前面所有的人。

感谢@二元长天笑 提供的翻译

## 样例 #1

### 输入

```
4
0 1 0 10
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2
0 0
```

### 输出

```
2
```

## 样例 #3

### 输入

```
10
1 1 3 0 0 0 2 1 0 3
```

### 输出

```
3
```

# 题解

## 作者：dalao_see_me (赞：6)

### 题目大意
有 $n$ 个人，第 $i$ 个人可以杀掉自己前面的 $a_i$ 个人。按照从前往后的顺序杀（也可以理解为同时挥刀）。求最后活几个人。
### 做法1
显然死亡的人是一段一段的。我们可以求出这些区间的左端点。再求出有多少个人不在这些区间里。

对于每个人求出他能杀到的范围再从后往前扫一遍即可。

时间复杂度 $O(n)$。

代码实现：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int a[N];
int n,L,ans;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int main(){
	n=read();L=n+1;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=n;i;i--){
		if(i<L)++ans;
		L=min(L,max(1,i-a[i]));//边界情况
	}
	return printf("%d",ans),0;
}
```
### 做法2
我们还可以用差分的方法来实现（不会差分请自行bfs）。

具体就是实现 $n$ 次区间加。

时间复杂度 $O(n)$。

代码实现：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int b[N];
int n,s,ans;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		int L=read();
		b[max(1,i-L)]++;//边界情况
		b[i]--;
	}
	for(int i=1;i<=n;i++){
		s+=b[i];
		if(!s)ans++;
	}
	return printf("%d",ans),0;
}
```
完结撒花~

---

## 作者：lizhous (赞：2)

### 1.题目：  
题目大意：有一个长 $n$ ( $1 \le n \le 10^6$ )的序列，第 $i$ 项的值为 $L_i$ ( $0 \le L_i \le 10^9$ )。初始序列未染色，对于每个整数 $i$ ( $1 \le i \le n$ )，它将会把他前 $L_i$ 个数染色（不包括自己）。现在求有多少个数不被染色。
### 2.分析：
由于是向前染色，我们需要先处理出每个节点染色区间的左端点，在新数组 $b$ 中记录。为了防止溢出，需要对 $1$ 取 $\max$ 。再使用变量 $len$ 记录当前已知最远的右区间。最后扫一遍求解即可。具体见代码。
### 3.代码：
```cpp
#include<iostream>
#include<cstdio> //头文件
using namespace std;
int n,a[1000001],b[1000001],ans,len;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]); //输入
		b[max(i-a[i],1)]=max(b[max(i-a[i],1)],i); //在b数组中标记左端点
	}
	for(int i=1;i<=n;i++)
	{
		len=max(len,b[i]); //在线处理len，节约空间
		if(i>=len) ans++; //注意有等于，因为染色不包括自己
	}
	printf("%d",ans); //输出
}
```


---

## 作者：empty_zhm (赞：2)

## 这是一个$O(n)$的算法
（~~大家的算法不都是O(n)的吗？~~）
### 说一下我的思路
把所有人及其爪子长度看成一个个线段并整合。     
（前面有大佬用的差分来整合，但我不是）  
先从最后一个人$A$开始记录爪子长度。（左端点最左的线段）     
每往前一个人$B$就判断是$A$的剩下的爪子长度长还是$B$现在爪子的长度长   
然后选择较为长的一段记录长度（也就是判断可合并的两条线段合并后的右端点是什么【左端点是不重叠的】）   
但注意一点，这里合并后的线段肯定是连续的，因为每一个人本身就会占据一条长度为1的线段，爪子的长度只是其向右延长的线段长度，所以线段至少端点会重叠。   
那么我们只用记录仅仅是重合的左端点和右端点形成的点的个数（还有第一个右端点）   
补充一点，这里的线段右端点是均匀分布且间隔为1，所以把所有线段都考虑到的方法就是枚举每一条线段的右端点。   
# 代码来咯！
### (当然是冷的，一定自己拿回去热热)
（我不知道为什么在Markdown里我代码里的制表符会很乱，看得不顺眼可以放在自己编译器看看QwQ）
```cpp
#include<bits/stdc++.h>
#define LL long long
#define N 1000010  
using namespace std;
int j,n,K[N],ans,cnt;//因为还要记录第一个右端点，就初始化0
int main()
{
	cin >> n;
	for(int i=1;i<=n;i++) scanf("%d",K+i);
	j=n;
	while(j>0)
	{
		if(cnt==0) ans++;//如果左端点与右端点重合了答案个数加1
		cnt--;//线段从当前点到右端点的长度减一（放这里是为了更新后不会再减一遍）
		cnt=max(K[j],cnt);//判断合并后线段的左端点位置
		j--;//考虑下一个线段
	}
	cout << ans;
}
```

### PS：正确性？我最蒟蒻了，自己证证？
（~~求过了~~）

---

## 作者：一只大龙猫 (赞：1)

这其实就是**区间修改，单点查询**的线段树模板。

我们可以统计一下每个人被别人杀的次数，最后遍历一下看看哪些人没有被杀，统计一下就行了，可以用线段树维护。

详见代码。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,m,tag[5000001],sum[5000001],a[5000001],l[5000001],ans;
inline int ls(int p){
	return p<<1;
}
inline int rs(int p){
	return p<<1|1;
}
void build(int o,int l,int r){
    tag[o]=0;
	if(l==r){
		sum[o]=a[l];
		return;
	}
	int mid=l+r>>1;
	build(ls(o),l,mid);
	build(rs(o),mid+1,r);
	sum[o]=sum[ls(o)]+sum[rs(o)];
	return;
}
void addtag(int o,int l,int r,int v){
	tag[o]+=v;
	sum[o]+=(r-l+1)*v;
	return;
}
void downtag(int o,int l,int r,int mid){
	if(tag[o]==0)return;
	addtag(ls(o),l,mid,tag[o]);
	addtag(rs(o),mid+1,r,tag[o]);
	tag[o]=0;
	return;
}
void update(int o,int l,int r,int x,int y,int v){
	if(l>y||r<x)return;
	if(x<=l&&r<=y){
		addtag(o,l,r,v);
		return;
	}
	int mid=l+r>>1;
	downtag(o,l,r,mid);
	update(ls(o),l,mid,x,y,v);
	update(rs(o),mid+1,r,x,y,v);
	sum[o]=sum[ls(o)]+sum[rs(o)];
	return;
}
int query(int o,int l,int r,int x,int y){
	if(l>y||r<x)return 0;
	if(x<=l&&r<=y)return sum[o];
	int mid=l+r>>1;
	downtag(o,l,r,mid);
	int v1=query(ls(o),l,mid,x,y),v2=query(rs(o),mid+1,r,x,y);
	return v1+v2;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&l[i]);
	}
	build(1,1,n);
	for(int i=1;i<=n;i++){
		if(l[i]>=i)update(1,1,n,1,i-1,1);//如果l[i]>=i，那么第i人前面的人都会被杀
		else update(1,1,n,i-l[i],i-1,1);//否则第i-l[i]人到第i-1人会被杀
	}
	for(int i=1;i<=n;i++){
		if(query(1,1,n,i,i)==0){
			ans++;
		}
	}
	printf("%d",ans);
	return 0;
}
```

时间复杂度 $O(n \log n)$，虽然略大，但还是足够过这道题的。

---

## 作者：Sophon (赞：1)

模拟即可。~~然而窝太菜想了好一会儿~~。由于一个人只能向前杀人，所以从后向前考虑。显然最后一个人必然存活，于是可以从最后一个人开始向前，在最远能够够得到的地方打上标记。然后向前扫描，不断将标记位（即最远够到的地方）向前推。如果扫描到了标记位的前一位，则表明标记位的前一位存活，计数$\;+1\;$。详见代码注释。

```cpp
#include <iostream>
using namespace std;

const int N = 1000000 + 10;

int len[N];//爪子长度

int n;//人数

int main()
{
	//关流同步，加速读入
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
    //读入
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> len[i];
	}

	int cnt = 1;//计数器
	int tag = n;//前文所说的标记位
	int index = n;//当前扫描到的位置
	
	while (tag >= 1)
	{
		while (index >= tag)
		{
			if (tag <= 1)//表明前面全部死亡，已经结束
			{
				cout << cnt << endl;
				return 0;//结束程序
			}
            //尽量向前推标记位
			if (tag > index - len[index])
			{
				tag = index - len[index];
			}
			index--;//扫描前一个位置
		}
        //前一个while条件被打破，即扫描到了标记位前一位
		cnt++;//计数器+1
		tag--;//强制前推标记位
	}
	//标记位出界，已经结束
	cout << cnt << endl;
	return 0;
}
```

---

## 作者：_HiKou_ (赞：0)

思路相对比较简单。（吗？）

思路：

1. 输入。
2. 死亡线的位置（即 $kl$，在这个范围内的人能被后面的人杀死）初始为 $n-a[n]$。（最后一个人够得着的地方）
3. 从后往前遍历。如果现在第 $i$ 个人在死亡线内，即 $kl≤i$ 时，默认这个人被杀死（$ans$ 不为所动）。否则代表后面没有人能杀到他，那么答案加 1。
4. 更新此时线的位置，为 $min(kl,a[i])$。（只能往前杀，所以找能杀到的i 的最小值）
5. 因为第一次判断时最后一个人会被判断为死亡（因为 $n-a[n]$ 不可能大于 $n$），所以答案初始化为 1（最后一个人后面没有人杀他）。
6. 输出。

CODE：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1919810];//不要介意qwq
int main(){
	int n,i,ans=1,kl;
	scanf("%d",&n);
	for(i=1;i<=n;i++)scanf("%d",&a[i]);
	kl=n-a[n];//初始化
	for(i=n;i>=1;i--)
	{
		if(kl>i)ans++;//判断
		kl=min(kl,i-a[i]);//更新死亡线位置
	}
	
	printf("%d",ans);
	return 0;
}
```

---

## 作者：duchengjun (赞：0)

# 题意

给每个人一把长为 $L_i$ 的大刀，铃声敲响时每个人的大刀挥起，也就是可以杀死自己前面的 $L_i$ 个人，找出铃响之后还有多少人幸存。

# 分析

考虑差分，因为第 $i$ 个人可以砍死自己前面的 $L_i$ 个人，所以在 $\max(1,i-L_i)\sim i-1$ 中每一个人都要死去，所以用差分数组即可。

前置芝士：

差分数组，和差分数组做前缀和是原数组。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
//此处为快读代码
const int N=1e6+10;
int n,L;
int a[N],sum,ans;
int main(){
	read_(n);
	for(int i=1;i<=n;i++){
		read_(L);
		a[i]--;
		a[max(1,i-L)]++;
	}
	for(int i=1;i<=n;i++){
		sum+=a[i];
		if(sum==0)
			ans++;
	}
	write_(ans);
	return 0;
}


```


---

## 作者：Xdl_rp (赞：0)

### 简要题意

共有 $n$ 个人，第 $i$ 个人可以将第 $i - 1$ 到 $i - a_i$ 个人都杀掉，问在铃响时（可以理解为同时看下去），有多少罪犯还活着。

solution
------------

将每一个人都遍历一遍（从后往前，因为最后一个人一定存活下来），如果当前能杀到的最远距离（设为 $tag$），$tag > i$，则说明第 $i$ 个人是能活下来的。每一次寻找最远距离，更新当前的值，每一次都判断 $tag$ 是否大于 $i$。如果大于（设最后活下来了人数为 $ans$），$ans$ 加上 $1$，否则不变，时间复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[1000005];
int main() {
	int n;
	scanf("%d", &n);
	for (register int i = 1; i <= n; i++) scanf("%d", &a[i]);//输入
	int tag = 1e9, ans = 0; //tag表示能杀到的最远距离（赋成一个比n大的数就行了），ans存储答案
	for (register int i = n; i >= 1; i--) {
		if (i < tag) ans++;//如果杀不到i这个位置，答案就加一
		tag = min(tag, max(i - a[i], 1));//更新最远距离
	}
	printf("%d\n", ans);//输出
	return 0;
}
```


---

## 作者：Hollis_Yang (赞：0)

### 题目大意：

有 $n$ 个人，每个人会杀掉自己前面的 $L_i$ 个人，问最后有多少个人活着。

### 解题思路：

很容易发现，第 $i$ 个人会杀掉 $[\max(1,i-l_i),i]$ 区间内的所有人。

我们用 $cf_i$ 表示第 $i$ 个人被杀的次数，么此把这个区间内的所有人被杀的次数 $+1$。

可以使用差分实现 $O(1)$ 的区间修改（不会差分的同学请自己 bdfs）。

最后统计一下被杀的次数为零的人数，这个人数就是答案。

总时间复杂度 $O(n)$。

### AC Code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define un unsigned
#define pb push_back
#define mp makepair
using namespace std;
template<typename T> inline void rd(T &x){
	x=0;char c=getchar();bool flag=false;
	while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
	while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	if(flag)x=-x;
}//快读 
template<typename T> inline void wr(T x){
   	short st[30],tp=0;
	if(x<0) putchar('-'),x=-x;
	do st[++tp]=x%10,x/=10; while(x);
	while(tp) putchar('0'|st[tp--]);
}//快输 
#define pk putchar(' ')
#define ed puts("")
int cf[1000006],i,x,n,ans=0;
signed main(){
	rd(n);
	for(i=1;i<=n;i++){
		rd(x);
		cf[max(1,i-x)]++;
		cf[i]--;
	}
	for(i=1;i<=n;i++){
		cf[i]=cf[i-1]+cf[i];
		if(cf[i]==0) ans++;
	}
	wr(ans);
}

```


---

