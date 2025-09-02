# Good String

## 题目描述

Let's call left cyclic shift of some string $ t_1 t_2 t_3 \dots t_{n - 1} t_n $ as string $ t_2 t_3 \dots t_{n - 1} t_n t_1 $ .

Analogically, let's call right cyclic shift of string $ t $ as string $ t_n t_1 t_2       t_3 \dots t_{n - 1} $ .

Let's say string $ t $ is good if its left cyclic shift is equal to its right cyclic shift.

You are given string $ s $ which consists of digits 0–9.

What is the minimum number of characters you need to erase from $ s $ to make it good?

## 说明/提示

In the first test case, you can erase any $ 3 $ characters, for example, the $ 1 $ -st, the $ 3 $ -rd, and the $ 4 $ -th. You'll get string 51 and it is good.

In the second test case, we can erase all characters except 0: the remaining string is 0000 and it's good.

In the third test case, the given string $ s $ is already good.

## 样例 #1

### 输入

```
3
95831
100120013
252525252525```

### 输出

```
3
5
0```

# 题解

## 作者：Skies (赞：4)

~~这题做了好久啊~~

思路比较复杂，但易懂

## 思路

经过简单推理可以发现

满足条件的字符串只能有两种形式
$$
1.ABABABAB...
$$

$$
2.AAAAAAAAA...
$$

记录每个数字出现的位置，存在vector中。

对于第二种情况，答案就是n-A的数量

对于第二种，用10*10的时间，分别枚举AB,然后爆搜最多有多少对AB，并更新答案

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
template <typename T>
inline void rd(T &x){
    x=0;char ch=getchar();bool f=false;
    while(!isdigit(ch)){if(ch=='-'){f=true;}ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    x=f?-x:x;
    return ;
}
template <typename T>
inline void wr(T x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) wr(x/10);
    putchar(x%10^48);
    return ;
}
int n;
const int N=2e5+10;
int a[N];
vector<int>s[10];//没有重复的 
//int cnt[10];
int _find(int num,int x)
{
	int l=0,r=s[num].size();
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(s[num][mid]<=x) l=mid+1;
		else r=mid;
	}
	if(r==s[num].size())return -1;
	else return s[num][r];
}
int main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	int T;
	rd(T);
	while(T--)
	{
		n=1;
		char c=getchar();
		while(c>='0'&&c<='9')
		{
			a[n]=c-'0';
			s[a[n]].push_back(n);
			c=getchar();
			n++;
		}
		n--;
		
		
		
		int ans=0;
		for(int i=0;i<=9;i++)
		{
			for(int j=0;j<=9;j++)
			{
				if(i==j)//AAAAAAAAAA...这种情况
				{
					int u=s[j].size();
					ans=max(ans,u);
					continue;
				}
                //ABABABABAB
				if(s[i].empty()||s[j].empty()||2*s[i].size()<=ans||2*s[j].size()<=ans)continue; //剪枝
				int now=0;
				int x=s[i][0];//起点
				while(1)
				{
					if(x==-1)break;
					int p=_find(j,x);
					if(p!=-1)
					{
						now++;
						x=_find(i,p);
						
					}else{
						break;
					}
				}
				ans=max(ans,2*now);
			}
		}
		wr(n-ans);putchar('\n');//删去的字符，用总长减
		for(int i=0;i<=9;i++)	
		{
			s[i].clear();//还原数组
		}
	}
	
	return 0;
}
```



---

## 作者：Fairicle (赞：4)

容易发现满足条件的字符串只会是 $aaaaaaaa...$ 或者 $abababab...$ 类型。

那么就分别计算两种情况。前一种方法显然。

由于题目告诉我们只可能是 $0-9$ 之间的数字，那么可能存在的 $abababab...$ 序列数只会有 $90$ 种。对每种进行计算即可。

code：
```cpp
#define ll long long
#define ri register int
#define N 200010
int n,num[12],p[10][10],ans;
char ch[N];
int main()
{
	int t=rd();
	while(t--){ans=0;
		memset(p,0,sizeof(p));
		scanf("%s",ch+1);int len=strlen(ch+1);memset(num,0,sizeof(num));
		for(ri i=1;i<=len;++i) num[ch[i]-'0']++;
		for(ri i=1;i<=len;++i){
			int k=ch[i]-'0';
			for(ri j=0;j<=9;++j){
				if(j==k) continue;
				if(p[j][k]%2!=0) p[j][k]++;
				if(p[k][j]%2==0) p[k][j]++;
			}
		}
		for(ri i=0;i<=9;++i) ans=max(ans,num[i]);
		for(ri i=0;i<=9;++i)
		for(ri j=0;j<=9;++j) if(i!=j) ans=max(ans,p[i][j]/2*2);
		cout<<len-ans<<endl;
	}
    return 0;
}

```


---

## 作者：Ericby666 (赞：2)

## [题目链接](https://www.luogu.com.cn/problem/CF1389C)
本题可以容易证得满足条件的字符串里的元素循环的周期长度为 $1$ 或 $2$，且当周期长度为 $2$ 时字符串长度为偶数。

所以我们只需要从 $0$ 到 $9$ 枚举两次，对于达成每种满足条件的字符串长度取最大值即可。（最终得到的字符串长度越大，则此时的操作次数最少）

AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,len,ans,now;
char s[200005];//最好使用char数组，因为string很难快速读入
int main(){
	scanf("%d",&t);
	while(t--){
		ans=0;
		scanf("%s",s);
		len=strlen(s);
		for(char i='0';i<='9';i++)
			for(char j='0';j<='9';j++){
				now=0;
				for(int k=0;k<len;k++)
					if((now%2==0 && s[k]==i) || (now%2==1 && s[k]==j))
						now++;//如果满足条件则当前字符串长度加1
				if(now%2==1 && i!=j)now--;//如果循环周期为二且字符串长度为奇数，当前字符串长度减1
				ans=max(ans,now);//取最大值
			}
		printf("%d\n",len-ans);
	}
	return 0;
}
```

---

## 作者：_Anchor (赞：1)

#### C题（性质）

##### Problem

对于一个字符串 $t_1,t_2,\cdots,t_n$，

我们定义它的右移为 $t_n,t_1,\cdots,t_{n-1}$

我们定义它的左移为 $t_2,t_3,\cdots,t_{1}$

现在请问对于给出的一个字符串，最少删掉多少个字符才能是这个字符串的左移和右移完全相同？

**注意**：题目保证字符串中的所有字符都是数字，$ t_x \in [\mathtt{0},\mathtt{1},\cdots,\mathtt{9}] \ $

##### Solution

我们发现字符集很小，于是可以考虑往枚举字符集上想

我们稍微按题意模拟一下就可以发现，这样的字符串成立，当且仅当这个字符串由某一个数，或者由某两个数交替构成

举个例子就是这个意思：

$AAAAAAA..AAA$或者$ABABABABAB...ABAB$

然后因为字符集很小，所以我们直接枚举所有可能的单个字符和所有可能的两个字符，去匹配过后看匹配最大的那个就是要保留的了

答案就是$len-ans$，也就是要删除的位置

时间复杂度$O(c\times n)$，$(c=100)$

---

## 作者：Zzzzzzzm (赞：1)

#### [题目链接](https://www.luogu.com.cn/problem/CF1389C)

### ~~数据超级水的~~
所以我们完全可以暴搜出奇迹

本篇题解解法：暴力枚举+简单剪枝水过

我们先来找对于数列的普遍规律
![](https://cdn.luogu.com.cn/upload/image_hosting/870hz9ya.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/nn1r8o5d.png)

我们可以确定一共有$100$种方式，即$00,01,02...98,99$。所以外层循环$0$~$9$，中层循环$0$~$9$，内层循环整个数列。我们可以知道，如果当前需要去掉的数＜当前最优解，就可以pass掉这种解法。在解题之前，我们可以确定出现次数最多的一个数，$ans-num[max]$。如果两个数$ij$个数$num[i]+num[j]≤num[max]$，也可以pass这种解法。

# Code


```cpp
#include<bits/stdc++.h>
using namespace std;

template <typename T>
inline void read(T&x){
    x=0;char ch=getchar();bool f=false;
    while(!isdigit(ch)){if(ch=='-'){f=true;}ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    x=f?-x:x;
    return;
}

template <typename T>
inline void write(T x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10^48);
    return;
}

string a;
int x[200005];
int num[10];
int w[15];
int n;

int main(){
	read(n);
	while(n--){
		memset(num, 0, sizeof(num));		//初始化0~9出现次数
		memset(w, 0, sizeof(w));			//初始化有的数
		cin >> a;
		if(a.size() <= 2){
			printf("0\n");
			continue;
		}
		int s = 0;							//记录出现的数的种数
		for(int i = 0; i < a.size(); i++){
			x[i+1] = a[i]-'0';
			if(num[x[i+1]] == 0){
				s++;
				w[s] = x[i+1];
			}
			num[x[i+1]]++;
		}
		int maxn = -0x3f3f3f3f;				//一个数最多出现次数
		for(int i = 0; i <= 9; i++){
			if(num[i] > maxn)	maxn = num[i];
		}
		int minn = a.size()-maxn;			//当前最优方案(用出现最多的数一个数)
		for(int i = 1; i <= s; i++){
			for(int j = 1; j <= s; j++){
				if(a.size()-(num[w[i]] + num[w[j]]) >= minn)	continue;
				int t = 0, ans = 0;
				for(int k = 1; k <= a.size(); k++){
					if(ans >= minn)	break;
					if(t % 2 == 0){			//如果为奇数个则为w[i]
						if(x[k] == w[i])
							t++;
						else	ans++;
						continue;
					}
					if(t % 2 == 1){			//如果为偶数个则为w[j]
						if(x[k] == w[j])
							t++;
						else	ans++;
						continue;
					}
				}
				if(i != j && t % 2 == 1)	ans++;		//如果总个数为奇数个并且为w[i] != w[j]，这还需去掉一个数
				if(i == j){
					if(ans <= minn)
						minn = ans;
				}
				else{
					if(ans <= minn)
						minn = ans;
				}
			}
		}
		write(minn);			//输出最优解minn
		printf("\n");
	}
}
```

#### 蒟蒻第一篇题解，望管理员通过

---

## 作者：dead_X (赞：1)

# 题意
给定一个字符串，让你删除最少的数字，使得剩余字符串 $a$ 满足 $\forall1\leq i\leq len-2,a_i=a_{i+2},a_{len-1}=a_1,a_{len}=a_2$ ，其中 $len$ 为 $a$ 的长度。
# 思路
易证 $len$ 为奇数时 $a$ 中所有字符均相同，为偶数时字符串的奇数位相同，偶数位相同。

然后直接枚举相同的字符即可。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
char ch[1000003];
int a[13];
int main()
{
	int T=read();
	while(T--)
	{
		scanf("%s",ch);
		for(int i=0; i<10; i++) a[i]=0;
		int len=strlen(ch);
		for(int i=0; i<len; i++) ++a[ch[i]-'0'];
		int ans=998244353;
		for(int i=0; i<10; i++) ans=min(ans,len-a[i]);
		int tmp;
		bool f;
		for(int i=0; i<10; i++) for(int j=0; j<10; j++) if(i!=j)
		{
			tmp=0,f=1;
			for(int k=0; k<len; k++) if(f) 
			{
				if(ch[k]-'0'==i) f=0;	
			}
			else
			{
				if(ch[k]-'0'==j) f=1,tmp+=2;
			}
			ans=min(ans,len-tmp);
		}
		printf("%d\n",ans);
	} 
    return 0;
}
```

---

## 作者：H6_6Q (赞：1)

### 翻译：
给你一个长度为 $n$ ( $n \le2 \times 10^5$ ) 的只包含数字字符的串 $t$ ，请你删除一些的字符，使得将第一个字符移动到末尾得到的串和将最后一个字符移动到开头得到的串相等。

求出最少要删除多少个字符。

### 思路：

先观察满足上述条件的字符串有什么特点，分类讨论下：

- 当一个串的长度为偶数时：
	
    假设我们有一个长度为 $6$ 的字符串 $A$ ：
    
    ![$$$$](https://cdn.luogu.com.cn/upload/image_hosting/fgjafvf9.png)
    
    那么将第一个字符移动到末尾得到的串和将最后一个字符移动到开头得到的串以及他们的相等关系就是：
    
    ![$$$$](https://cdn.luogu.com.cn/upload/image_hosting/r95534ch.png)
    
    那么把这些相等关系整理出来就是：
    
    $A_6=A_2=A_4=A_6$
    
    $A_1=A_3=A_5=A_1$
    
    显然，奇数位置上的字符都相等，偶数位置上的字符也都相等。
    
    所以我们得出结论 1 ：当一个满足条件串的串长为为偶数时，那么这个串一定是 $ababab...$ 的形式。
    
- 当一个串的长度为奇数时：

	假设我们有一个长度为 $7$ 的字符串 $A$ ：
    
    ![$$$$](https://cdn.luogu.com.cn/upload/image_hosting/1vlb7l1m.png)
    
    那么将第一个字符移动到末尾得到的串和将最后一个字符移动到开头得到的串以及他们的相等关系就是：
    
    ![$$$$](https://cdn.luogu.com.cn/upload/image_hosting/egdsj05p.png)
    
    那么把这些相等关系整理出来就是：
    
    $A_7=A_2=A_4=A_6=A_1=A_3=A_5=A_7$
    
    显然，所有位置上的字符都相等。
    
    所以我们得出结论 2 ：当一个满足条件串的串长为为奇数时，那么这个串一定是 $aaaaaa...$ 的形式。
    
综上，我们只要找到一个最长的子串，使得这个串为 $ababab...$ 的形式且长度为偶数 或者 $aaaaaa...$ 且长度为奇数。

因为字符串仅有数字字符构成，所以我们可以直接枚举 $a$ 和 $b$，然后贪心地取最大，最后用总长减去能取出的最长的子串即可。

### Code：
```
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<bitset>
#include<string>
#include<cstdio>
#include<vector>
#include<cmath>
#include<queue>
#include<map>
 
using namespace std;
 
int read()
{
	int ans=0,f=1;
	char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
	return ans*f;
}
 
const int N=2e5+5;
int t,n,ans;
char s[N];
 
int main()
{
	t=read();
	while(t--)
	{
		ans=0;
		scanf("%s",s+1);
		n=strlen(s+1);
		for(int a=0;a<=9;++a)
			for(int b=0;b<=9;++b)
            //枚举a和b
			{
				int tmp=0;
                //tmp为已经取出来的长度
				for(int i=1;i<=n;++i)
					if(tmp%2==0&&s[i]-'0'==a||tmp%2==1&&s[i]-'0'==b)
                    //贪心取
						tmp++;
				if(tmp%2==1&&a!=b)
                //如果取出的长度为奇数，那么只有a=b才合法，否则只能变成偶数
					tmp--;
				ans=max(ans,tmp);
			}
        //用总长减去最长能取出的长度就是最少删去字符的数量
		printf("%d\n",n-ans);
	}
	return 0;
} 
```


---

## 作者：钓鱼王子 (赞：1)

分结果 $n$ 的奇偶性讨论。

当 $n$ 为奇数时，$s_1=s_3=s_5=...=s_n=s_2=s_4...=s_{n-1}$，记录出现次数最多的字符。

当 $n$ 为偶数时，$s_1=s_3=...=s_{n-1},s_2=s_4=...=s_n$，也就是 $0101010101...$ 的形式，此时只需要枚举循环节，判断需要删多少字符即可。

```cpp
#include<bits/stdc++.h>
#define re register
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
} 
using namespace std;
int n,m,vis[26],ans,t,w;
char s[200002];
inline int calc(re int x,re int y){
	re int pos=1,xx=0;
	while(1){
	while(s[pos]!=x+'0'&&pos<=n)++pos;++pos;
	while(s[pos]!=y+'0'&&pos<=n)++pos;
	if(pos>n)break;++pos;
	xx+=2;
	}
	return n-xx;
}
int main(){
	t=read();
	while(t--){
		scanf("%s",s+1);
		n=strlen(s+1);memset(vis,0,sizeof(vis));
		for(re int i=1;i<=n;++i)++vis[s[i]-'0'];
		w=0;for(re int i=0;i<=9;++i)w=max(w,vis[i]);
		ans=n-w;
		for(re int i=0;i<=9;++i)for(re int j=0;j<=9;++j)ans=min(ans,calc(i,j));
		printf("%d\n",ans);
	}
}
```


---

## 作者：huayucaiji (赞：1)

~~这个题比B简单吧~~

我们可以通过题目得出以下结论：

$$s_2\ \ s_3\ \ s_4.....s_{n-1}\ \ s_n\ \ s_1\\=s_n\ \ s_1\ \ s_2.....s_{n-3}\ \ s_{n-2}\ \ s_{n-1}$$

所以我们有 $s_1=s_3=s_5=....s_{n-1}=q$，$s_2=s_4=s_6=.....s_{n}=p$。

我们只需要枚举 $p,q$ 即可，每次枚举出来后，顺次统计以下最少要删多少字符，用贪心一个一个扫就是最优的，这里就不再证明了。但是我们还有一些特殊情况要处理。

如果我们最后删减版序列是 $pqpqp$。那么我们得出的两序列是 $ppqpq$ 和 $qpqpp$。显然在 $p\neq q$ 时不等。**所以当 $p\neq q$ 且 $len$ 是奇数时，删去的数还要在加一。** 

**注意特判 $len=1$。**

```cpp
//Don't act like a loser.
//You can only use the sode for studying or finding mistakes
//Or,you'll be punished by Sakyamuni!!!
#include<bits/stdc++.h>
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

int n;
string s;

signed main() {
	
	int t=read();
	while(t--) {
		cin>>s;
		n=s.size();
		
		if(n==1) {
			cout<<0<<endl;//特判 n=1
			continue;
		}
		
		int ans=n;
		for(int i=0;i<=9;i++) {
			for(int j=0;j<=9;j++) {
				int num=0,sum=0;//num记录当前应该匹配哪个数
				
				for(int k=0;k<n;k++) {
					if(!num) {
						if(s[k]-'0'!=i) {
							sum++;
						}
						else {
							num=1-num;
						}
					}//分类
					else {
						if(s[k]-'0'!=j) {
							sum++;
						}
						else {
							num=1-num;
						}
					}
				}
				if(i!=j&&num) {
					sum++;//删去的数+1
				}
				ans=min(ans,sum);
			}
		}
		
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：Isshiki_Hugh (赞：1)

~~C明显比B简单啊喂！~~

题设要我们对字符串$S$进行操作，使$S$删除$p$个字符后，满足如下条件：

- 设$S_a$为将字符串$S$的首位放到最后
- 设$S_b$为将字符串$S$的末位放到最前
- $S_a$等于$S_b$

现求$p$的最小值。

我们仔细想一想，看一下样例就会发现，最后合法的情况只有两种：

- 1.单个字符$m$的自循环，即$mmmmmmmm...$
- 2.连个字符$mn$的**循环**节，即$mnmnmnmn ...$
	- 特别的，诸如$mnm$的循环是不合法的，$mnmn$是合法的，即length必须为偶数
    
想到这里就很好处理了，第一种情况我们枚举一下每一个字符，看看最多的是哪个然后更新答案；

```cpp
inline int solve1(int x){
    int t = 0;
    rep(i,1,len) if(ch[i] - '0' == x) ++t;
    return t;
}
```

第二种情况枚举循环节然后看看最长的是哪个更新答案

```cpp
inline int solve2(int x,int y){
    int t = 0;
    int i = 1;
    while(i <= len){
        while(ch[i] - '0' != x && i <= len) ++i;
        if(ch[i] - '0' == x) ++t;
        while(ch[i] - '0' != y && i <= len) ++i;
        if(ch[i] - '0' == y) ++t;;
    }
    return t - t%2;
}
```

### 完整代码：

```cpp
#include<map>
#include<set>
#include<cmath>
#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define rep(i,a,b) for(register int i = (a);i <= (b);++i)
#define per(i,a,b) for(register int i = (a);i >= (b);--i)  
typedef long long ll;
typedef unsigned long long ull;
using std::string;using std::cin;using std::cout;

int _,len,ans,tmp;
char ch[200005];

inline int solve1(int x){
    int t = 0;
    rep(i,1,len) if(ch[i] - '0' == x) ++t;
    return t;
}

inline int solve2(int x,int y){
    int t = 0;
    int i = 1;
    while(i <= len){
        while(ch[i] - '0' != x && i <= len) ++i;
        if(ch[i] - '0' == x) ++t;
        while(ch[i] - '0' != y && i <= len) ++i;
        if(ch[i] - '0' == y) ++t;;
    }
    return t - t%2;
}

int main(){
    std::ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("in.in", "r", stdin);
    cin >> _;
    while(_--){
        cin >> ch+1;
        len = strlen(ch+1);
        ans = len-2 , tmp = 1;
        rep(i,0,9) tmp = std::max(tmp,solve1(i));
        ans = std::min(ans,len - tmp);
        tmp = 2;
        // cout << ans << "\n";
        rep(i,0,9){
            rep(j,0,9){
                if(i == j) continue;
                tmp = std::max(tmp,solve2(i,j));
                ans = std::min(ans,len - tmp);
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
```

---

## 作者：bigclever (赞：0)

## 思路：
定义字符串 $t$ 的长度为 $|t|$。

如果一个字符串 $s$ 的左移和右移相等，那么易知
$$s_i = \begin{cases}
s_{i+2} & i+2 \le |s| \\
s_{i+2-|s|} & i+2 \gt |s|
\end{cases}$$
所以只有形如 $ABABAB \dots$ 的字符串可以满足。那我们只要枚举所有可能的 $AB$（$00 \sim 99$），依次计算将 $s$ 变为 $ABABAB \dots$ 所需要删去的字符数，最后取最小值即可。

时间复杂度 $O(|s|)$。
## Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int cal(string s,string tar){//计算s中形如ABABAB...的字符串中最多的字符数
	int cnt=0;
	if(tar[0]==tar[1]){//特判A=B的情况
		for(int i=0;i<s.size();i++)cnt+=(s[i]==tar[0]);
		return cnt;
	}
	bool f=(s[0]==tar[0]);
	for(int i=1;i<s.size();i++){
		if(f&&s[i]==tar[1])cnt++,f=false;
		else if(s[i]==tar[0])f=true;
	}
	return cnt*2;
}
int main(){
	int t; cin>>t;
	while(t--){
		string s; cin>>s;
		if(s.size()==1){puts("0");continue;}
		int ans=0;
		for(char i='0';i<='9';i++)
			for(char j='0';j<='9';j++){
				string tar="";
				tar.push_back(i),tar.push_back(j);
				ans=max(ans,cal(s,tar));//答案取最小，包含AB的个数就要尽量多，所以ans取最大值
			}
		cout<<s.size()-ans<<endl;
	}
	return 0;
}
```

---

## 作者：Miraik (赞：0)

赛时居然$WA$了$4$次。。。害我掉了$rating$

首先考虑：

只有以下三种情况为$Good$ $String$ :

1.为空串（可以不考虑，肯定不是最优解）

2.只有一种字符

3.只包含两种字符，且为 $xyxyxyxy$这种排列，以$x$开头，以$y$结尾。

显然易证当包含三种及以上字符时，不可能为$Good$ $String$。

然后我们只需枚举0到9的排列，在所有合法方案中取$\min$即可。

具体代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
int t,l,res,k,ans;
char s[200005],x,y;
inline int _min(int x,int y){return x<y?x:y;}
int main(){
	t=read();
	while(t--){
		scanf("%s",s);
		l=strlen(s);
		ans=l-1;//初始化，删至只剩一个字符
		for(char i='0';i<='9';i++)
		    for(char j='0';j<='9';j++){
		    	res=0;
		    	x=i;
		    	for(int k=0;k<l;k++)//以xyxyxyxy的方式枚举
		    	    if(x==i){
		    	    	if(s[k]==j)x=j;
		    	    	else res++;
		    	    }
		    	    else{
		    	    	if(s[k]==i)x=i;
		    	    	else res++;
		    	    }
		    	if(i==j||(l-res)%2==0)ans=_min(ans,res);
		    	//i==j 只剩一种字符 (l-res)%2 剩下的序列长度为偶数
		    }
		printf("%d\n",ans);
	}
	return 0;
}

```


---

## 作者：kradcigam (赞：0)

简要题意：

>对于一个字符串 $t_1,t_2,\cdots,t_n$，
>
>我们定义它的右移为 $t_n,t_1,\cdots,t_{n-1}$；
>
>我们定义它的左移为 $t_2,t_3,\cdots,t_{1}$。
>
>现在请问对于给出的一个字符串，最少删掉多少个字符才能是这个字符串的左移和右移完全相同？

我们来分析一下性质，比较一下右移和左移

右移：$t_n,t_1,\cdots,t_{n-1}$

左移：$t_2,t_3,\cdots,t_{1}$

要使这 $2$ 个东西相同就必须使得 $t_2=t_n,t_1=t_3,\cdots,t_{n-1}=t_1$

我们举个具体的例子，假设 $n=8$。

右移：$t_8,t_1,t_2,t_3,t_4,t_5,t_6,t_7$

左移：$t_2,t_3,t_4,t_5,t_6,t_7,t_8,t_1$

显然，$t_2=t_4=t_6=t_8$，$t_1=t_3=t_5=t_7$。

可以证明当 $n$ 为偶数时，这个字符串的循环节必须为 $2$。

我再来试试 $n=7$。

右移：$t_7,t_1,t_2,t_3,t_4,t_5,t_6$

左移：$t_2,t_3,t_4,t_5,t_6,t_7,t_1$

显然，$t_1=t_3=t_5=t_7=t_2=t_4=t_6$

可以证明当 $n$ 为奇数时，这个字符串的循环节必须为 $1$。

这 $2$ 个东西笔者都试着证明了一下，有些麻烦，这里就不放了。

```cpp
// Problem: C. Good String
// Contest: Codeforces - Educational Codeforces Round 92 (Rated for Div. 2)
// URL: https://codeforc.es/contest/1389/problem/C
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
template<typename T>inline void read(T &FF){
	T RR=1;FF=0;char CH=getchar();
	for(;!isdigit(CH);CH=getchar())if(CH=='-')RR=-1;
	for(;isdigit(CH);CH=getchar())FF=(FF<<1)+(FF<<3)+(CH^48);
	FF*=RR;
}
const int MAXN=2e5+10;
int s[11][2];
int work(){
	memset(s,0,sizeof(s));
	string st;cin>>st;
	int n=st.size(),ans=n;
	st=' '+st;
	for(int i=0;i<=9;i++){
		int s=0;
		for(int j=1;j<=n;j++)
			if(st[j]!=char(i+48))s++;
		ans=min(ans,s);
	}
	for(int i=0;i<=9;i++)
		for(int j=0;j<=9;j++){
			int s=0;
			for(int k=1;k<=n;k++){
				if(s%2==0){
					if(st[k]==char(i+48))s++;
				}else{
					if(st[k]==char(j+48))s++;
				}
			}
			if(s%2==1)s--;
			ans=min(ans,n-s);
		}
	cout<<ans<<endl;
	return 0;
}
int main(){
	int T;read(T);
	while(T--){
		//memset
		work();
	}
	return 0;
};
```



---

## 作者：fsy_juruo (赞：0)

### 题意简述

* 定义一个字符串 $t_1t_2t_3 \cdots t_n$ 是好的，当且仅当 $t_2t_3 \cdots t_nt_1 = t_nt_1 \cdots t_{n-2}t_{n-1}$
* 给定字符串，问至少要删几个字符才能使这个字符串是好的。
* 多测，$2 \leq |s| \leq 2 \times 10^5$，$\sum |s| \leq 2 \times 10^5$，字符集为阿拉伯数字。

### 题解

* 不难发现，一个字符串是好的，当且仅当 $t_2 = t_4 = t_6 = \cdots$ 且 $t_1 = t_3 = t_5 = \cdots$。
* 于是符合条件的字符串只有两种：（1）由一种字符构成的字符串（2）由两种字符交替构成的字符串，且字符串长度为偶数。
* 对于第（1）种字符串，直接统计字符个数即可。
* 对于第（2）种字符串，由于字符集大小仅为 $10$，可以考虑暴力枚举这两个字符并计算答案。具体细节详见代码注释。
* 单次时间复杂度 $\mathcal{O}(n)$。

### 代码

```cpp
#include <bits/stdc++.h>
#define LL long long
#define ULL unsigned long long
#define LD long double
#define reg register
#define _rep(i, x, y) for(int i = x; i <= y; i++)
#define _per(i, x, y) for(int i = x; i >= y; i--)
template <typename T>
inline void read(T &x) {
	x = 0; T f = (T) 1;
	char c = getchar();
	for(; !isdigit(c); c = getchar()) {if(c == '-') f = -f;}
	for(; isdigit(c); c = getchar()) x = x * 10 + c - 48;
	x *= f;
}
template <typename T, typename... Args>
inline void read(T& x, Args&... args) {
    read(x); read(args...);
}
template <typename T>
inline void write(T x) {
	if(x < 0) {x = -x; putchar('-');}
	if(x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
template <typename T>
inline void writesp(T x, char sp = ' ') {write(x); putchar(sp);}
const int inf = 1e9 + 10, maxN = 2e5 + 10;
int t, n, cnt[10], Cnt[maxN][10];
std::string s;
int main() {
	read(t);
	while(t--) {
		memset(cnt, 0, sizeof(cnt));
		memset(Cnt, 0, sizeof(Cnt));
		getline(std::cin, s);
		int len = s.size(), ans = inf;
		_rep(i, 1, len) {
			cnt[s[i - 1] - '0']++; 
			Cnt[i][0] = Cnt[i - 1][0] + (s[i - 1] == '0');
			Cnt[i][1] = Cnt[i - 1][1] + (s[i - 1] == '1');
			Cnt[i][2] = Cnt[i - 1][2] + (s[i - 1] == '2');
			Cnt[i][3] = Cnt[i - 1][3] + (s[i - 1] == '3');
			Cnt[i][4] = Cnt[i - 1][4] + (s[i - 1] == '4');
			Cnt[i][5] = Cnt[i - 1][5] + (s[i - 1] == '5');
			Cnt[i][6] = Cnt[i - 1][6] + (s[i - 1] == '6');
			Cnt[i][7] = Cnt[i - 1][7] + (s[i - 1] == '7');
			Cnt[i][8] = Cnt[i - 1][8] + (s[i - 1] == '8');
			Cnt[i][9] = Cnt[i - 1][9] + (s[i - 1] == '9'); // 特别暴力的字符数量前缀和
		}
		_rep(i, 0, 9) ans = std::min(ans, len - cnt[i]); // 第（1）种字符串
		_rep(i, 0, 9) {
			_rep(j, 0, 9) {
				if(i == j) continue; // i==j 你统计干嘛？
				int qwq = 0, flg = 1;
				_rep(k, 1, len) {
					if(s[k - 1] == '0' + j) {
						if(Cnt[k - 1][i] - Cnt[flg - 1][i]) { // 如果上一个字符与这一个字符之间有目标字符
							qwq = qwq + 2; // 长度加上目标字符与这个字符，故要 +2
							flg = k; // 更新字符位置
						}
					}
				}
				ans = std::min(ans, len - qwq);
			}
		}
		writesp(ans, '\n');
	}
	return 0;
}
```

---

