# Test

## 题目描述

给定 $3$ 个字符串 $s_1,s_2,s_3$，试求一个字符串，使 $s_1,s_2,s_3$ 都是这个字符串的子串，并使这个字符串最短。输出最短字符串的长度 $l$。

## 说明/提示

$1 \leq |s_1|,|s_2|,|s_3| \leq 10^5$。

## 样例 #1

### 输入

```
ab
bc
cd
```

### 输出

```
4
```

## 样例 #2

### 输入

```
abacaba
abaaba
x
```

### 输出

```
11
```

# 题解

## 作者：NekoPass (赞：23)

### Click [Here](https://www.luogu.org/blog/NekoPass/solution-cf25e) For Better Experience
# 第一篇黑题题解OwO，想想还有些兴奋呢（虽然这道题可能含水量有些大......）
------------
~~一开始看错题目还以为是要求最长的公共子串，结果想半天想不出来，看来我还是太蒻~~

不过如果只是要求一个包含s1,s2,s3的最短字符串S的话，这道题就变成了一道暴力玄学题了。

我们假设三个字符串是同一个字符串S的不同部分（或者说是不同的区间），那么这个问题就转化成三个区间的覆盖有多少种情况了。

首先考虑只有s1和s2时的情况，如图：

![](https://cdn.luogu.com.cn/upload/pic/53011.png)

我们发现相离这种情况是没有意义的，因为如果两个子串之间没有重合部分，那么相切（就是指s1的最后一个字符和s2的第一个字符相接）就是最优解。

另外我们还发现，求s1和s2相交部分的求法就是求出s2的next数组然后进行一遍[KMP](https://www.luogu.org/blog/NekoPass/solution-p3375)，只不过这一次我们求的是匹配结束以后s2匹配到的位置是哪里。

同理，s3和另外两个字符串的组合串之间的关系也是一样的，所以我们只需要对三个字符串的顺序进行暴力枚举之后求他们相接起来后的长度的最小值就可以得到答案了喵~~

最后献上常数巨大的蒟蒻代码
```cpp
#include <cstdio>
#include <cstring>
#define min(a,b) ((a)<(b))?(a):(b)
using namespace std;
const int INF=2147483646;
int nxt[4][100050],l[4];
char s[4][100050];
inline void Pre(){
    for(int f=1;f<4;++f){//求出三个字符串的next数组 
        int p=0,len=l[f];
        for(int i=2;i<=len;++i){
            while(p&&s[f][i]!=s[f][p+1]) p=nxt[f][p];
            //PS：nxt[f][p]之前被我打成了nxt[i][p]结果WA了n次QAQ 
            if(s[f][i]==s[f][p+1]) ++p;
            nxt[f][i]=p;
        }
    }
    return ;
}
int f(int a,int b,int c){ 
    int ans=INF,p1=0;
    int al=l[a],bl=l[b],cl=l[c];
    for(int i=1;i<=al;++i){
        while(p1&&s[b][p1+1]!=s[a][i]) p1=nxt[b][p1];
        if(s[b][p1+1]==s[a][i]) ++p1;
        if(p1==bl){
            p1=-1;//-1代表b是a的子串 
            break;
        }
    }
    if(p1==-1){//如果b是a的子串，就直接让c和a匹配
		//所以不会熟练运用子程序的我只好再copy一次 
        int p=0;
        for(int i=1;i<=al;++i){
            while(p&&s[c][p+1]!=s[a][i]) p=nxt[c][p];
            if(s[c][p+1]==s[a][i]) ++p;
            if(p==cl){
                p=-1;
                break;
            }
        }
        if(p==-1) ans=al;
        else ans=al+cl-p;
    }
    else{
    	//否则，先用c匹配a再从a，b相交位置开始匹配b 
        int p=0;
        for(int i=1;i<=al;++i){
            while(p&&s[c][p+1]!=s[a][i]) p=nxt[c][p];
            if(s[c][p+1]==s[a][i]) ++p;
            if(p==cl){
                p=-1;
                break;
            }
        }
        if(p!=-1){
            int p2=p;
            for(int i=p1+1;i<=bl;++i){
                while(p2&&s[c][p2+1]!=s[b][i]) p2=nxt[c][p2];
                if(s[c][p2+1]==s[b][i]) ++p2;
                if(p2==cl){
                    p2=-1;
                    break;
                }
            }
            if(p2==-1) ans=al+bl-p1;
            else ans=al+bl-p1 + cl -p2;
        }
        else ans=al+bl-p1;
    }
    return ans;
}
int main(){
    scanf("%s%s%s",s[1]+1,s[2]+1,s[3]+1);
    int ans=INF;
    l[1]=strlen(s[1]+1);l[2]=strlen(s[2]+1);l[3]=strlen(s[3]+1);
    Pre();
    ans=min(ans,f(1,2,3));ans=min(ans,f(1,3,2));
    ans=min(ans,f(2,1,3));ans=min(ans,f(2,3,1));
    ans=min(ans,f(3,2,1));ans=min(ans,f(3,1,2));
    //真·暴力枚举排列顺序 
    printf("%d",ans);//快乐AC喵(OωO)
    return 0;
}
```
### 真的不来nekopass的[喵窝](https://www.luogu.org/blog/NekoPass/)看看喵？

---

## 作者：0xFF (赞：10)

#### 题意简述


------------
给定三个字符串 $s1,s2,s3$。找出一个最短的字符串使得三个字符串都为其子串，输出其长度。

#### 题目分析


------------
首先考虑给定两个字符串的时候的情况：

- 求出两个字符串的最长的公共子串
- 最短字符串即为两字符串的总长度减去最长公共子串的长度

由以上的情况可以扩展到给定三个字符串的时候的情况

首先将三个字符串分别匹配，讨论如下情况：
- 若三个字符串不互相包含对方则答案为三字符串的总长度减去第一个字符串与第二个字符串的最大匹配长度，再减去第二个字符串与第三字符串的最大匹配长度
- 若其中两字符串包含于另一字符串，则答案为该字符串的长度
- 若其中一字符串包含于另外两字符串中，则本题变为考虑两个字符串进行匹配的情况

很明显的可以知道本题需要用 ```KMP``` 来进行字符串的匹配。与 [【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)唯一的不同在于本题处理出来的 ```next``` 数组需要增加一维记录处理的是第几个字符串。

#### 代码实现


------------

```cpp
#include<bits/stdc++.h>
using namespace std;
const int INF=2147483647; 
int nxt[4][100001];
bool ok[4];
void getnext(int m,char s2[],int t){ 
    int j=0;
    for(int i=2;i<=m;i++){
        while(j!=0&&s2[j+1]!=s2[i])j=nxt[t][j];
        if(s2[j+1]==s2[i])j++;
        nxt[t][i]=j; 
    }
    return;
}
int KMP(int n,int m,char s1[],char s2[],int t){ 
    int j=0,cnt=0;
    for(int i=1;i<=n;i++){
        while(j!=0&&s2[j+1]!=s1[i])j=nxt[t][j];
        if(s2[j+1]==s1[i])j++;
        if(j==m){
	        return -1;
	        j=nxt[t][j];
        }
    }
    return j;
}
char s[4][100001];
int len[4];
int K[4][4];
int main(){
	memset(nxt,0,sizeof nxt);
    scanf("%s%s%s",s[1]+1,s[2]+1,s[3]+1); 
    len[1]=strlen(s[1]+1); 
    len[2]=strlen(s[2]+1);
    len[3]=strlen(s[3]+1);
    for(int i=1;i<=3;i++){ 
	    getnext(len[i],s[i],i);
	    for(int j=1;j<=3;j++){ 
	        if(i==j)continue;
	        K[j][i]=KMP(len[j],len[i],s[j],s[i],i);
	    }
    }
    int ans=INF;
    for(int i=1;i<=3;i++){ 
    	for(int j=1;j<=3;j++){
	        for(int k=1;k<=3;k++){
	        if(i==j||j==k||i==k)continue; 
	        int sum=len[i]+len[j]+len[k]-K[i][j]-K[j][k]; 
	        if(K[i][j]>=0&&K[j][k]>=0)ans=min(ans,sum); 
		        else{
		            if(K[i][j]<0&&K[i][k]<0)
						ans=min(ans,len[i]); 
		            else if(K[i][j]<0)
						ans=min(ans,sum+K[i][j]+K[j][k]-len[j]-K[i][k]); 
		            if(K[j][k]<0)
						ans=min(ans,sum+K[j][k]-len[k]); 
		        }
	        }
	    }
    }
    printf("%d\n",ans); 
    return 0;
}
```


---

## 作者：EternalEpic (赞：8)

## 双倍经验题！！！（同SP7155 Test）

但别高兴太早，SPOJ上数据很毒瘤，我CF上用了string的一些内置函数卡过，交到SPOJ上就wa了。

所以还得字符数组加KMP。

什么？你不会KMP, （~~那你可以O（nm）暴力枚举啊！~~ ）请跳转[P3375 【模板】KMP字符串匹配](https://www.luogu.org/problemnew/show/P3375)

字符数组里的strcat函数也是很好用的，题解里貌似有人手写，~~很坚强~~

这里，我要介绍一下，我的一个懒人写法。因为3个char[]要依次匹配，为什么不能外嵌全排列呢？

大家可看我短小的主程序：

```cpp
while(scanf("%s%s%s", s[0], s[1], s[2]) != EOF)
{
	int ret, ans = INT_MAX;
	for (int i = 0; i < 3; ++i) q[i] = i;
	do {
		ret = solve(s[q[0]],s[q[1]],s[q[2]]);
		chkmin(ans, ret);
	} while (next_permutation(q, q + 3));
	writeln(ans);
} 
```

如果没有nextpermutation，可能就很麻烦，而且容易错了吧！

其次，就是kmp和计算答案了。

## Function：

```cpp
inline int KMP(char* s1,char* s2)
{
    int n = strlen(s1);
    int m = strlen(s2);
    int j = -1;
    p[0] = -1;
    for (register int i = 1; i < m; i++)
    {
        while (j >= 0 && s2[i] != s2[j + 1]) j = p[j];
        if (s2[i] == s2[j+1]) j++;
        p[i] = j;
    }
    j = -1;
    for (register int i = 0; i < n; i++)
    {
        if (j == m - 1) return 0;
        while (j >= 0 && s1[i] != s2[j + 1]) j = p[j];
        if (s1[i] == s2[j+1]) j++;
    }
    return m - 1 - j;
}
 
inline int solve(char* s1,char* s2,char* s3)
{ 
    int ret;
    ret = KMP(s1, s2);
    str[0] = '\0';
    strcat(str, s1);
    strcat(str, s2 + strlen(s2) - ret);
    ret = KMP(str, s3);
    return ret + strlen(str);
}
```

完整代码如下
## CODE:

```cpp
//Program written by Liu Zhaozhou ~~~
#include <bits/stdc++.h>
#include <algorithm>
#include <queue>
#include <set>
#include <vector>
#include <deque>
#include <string>

#define lowbit(x) x & -x

#pragma GCC optimize(2)

using namespace std;

namespace Base {
inline char gc(void)
{
	static char buf[100000], *p1 = buf, *p2 = buf;
	return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}

#define gc() getchar()

template <class T> inline void read(T &x)
{
	T flag = 1; x = 0; register char ch = gc();
	for (; !isdigit(ch); ch = gc()) if (ch == '-') flag = -1;
	for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch & 15);
	x *= flag; return;
}

template <class T> inline void write(T x) {
	if (x < 0) putchar('-'), x = -x;
	register T y = 1; int len = 1;
	for (; y <= x / 10; y *= 10) ++len;
	for (; len; --len, x %= y, y /= 10) putchar(x / y + 48);
}

template <class T> inline void writeln(T x) {write(x); puts("");}
template <class T> inline void writeln(T x, char c) {write(x); putchar(c);}
template <class T> inline void writeln(char c, T x) {putchar(c); write(x);}

template <class T> inline void chkmax(T &x, const T y) {x > y ? x = x : x = y;}
template <class T> inline void chkmin(T &x, const T y) {x < y ? x = x : x = y;}

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

#define Ms(arr, opt) memset(arr, opt, sizeof(arr))
#define Mp(x, y) make_pair(x, y)

inline void file(string str) {
	freopen((str + ".in").c_str(), "r", stdin);
	freopen((str + ".out").c_str(), "w", stdout);
}
}

using namespace Base;

enum {
	N = 200005,
	M = 100005
};
 
char str[N];
char s[3][M];
int p[N], q[3];
 
inline int KMP(char* s1,char* s2)
{
    int n = strlen(s1);
    int m = strlen(s2);
    int j = -1;
    p[0] = -1;
    for (register int i = 1; i < m; i++)
    {
        while (j >= 0 && s2[i] != s2[j + 1]) j = p[j];
        if (s2[i] == s2[j+1]) j++;
        p[i] = j;
    }
    j = -1;
    for (register int i = 0; i < n; i++)
    {
        if (j == m - 1) return 0;
        while (j >= 0 && s1[i] != s2[j + 1]) j = p[j];
        if (s1[i] == s2[j+1]) j++;
    }
    return m - 1 - j;
}
 
inline int solve(char* s1,char* s2,char* s3)
{ 
    int ret;
    ret = KMP(s1, s2);
    str[0] = '\0';
    strcat(str, s1);
    strcat(str, s2 + strlen(s2) - ret);
    ret = KMP(str, s3);
    return ret + strlen(str);
}

signed main(void) {
	//file("");
	/*我刘兆洲作为多年卡常选手不会快读string简直了。。。*/
	/*改为字符数组重写试试*/
	
	while(scanf("%s%s%s", s[0], s[1], s[2]) != EOF)
	{
		int ret, ans = INT_MAX;
		for (int i = 0; i < 3; ++i) q[i] = i;
		do {
			ret = solve(s[q[0]],s[q[1]],s[q[2]]);
	    	chkmin(ans, ret);
		} while (next_permutation(q, q + 3));
		writeln(ans);
	} 
	
    return 0;
}

/**/


```

谢谢兹磁！！！


---

## 作者：chufuzhe (赞：5)

做法：字符串哈希

分类讨论：

- $1$.$B$ 为 $A$ 的子串

枚举 $B$ 在 $A$ 中的位置

- $2$.$A$ 为 $B$ 的子串

枚举 $A$ 在 $B$ 中的位置

- $3$.$A$ 和 $B$ 有相同长度的前缀和后缀

枚举前缀后缀长度

- $4$.$A$ 和 $B$ 没有相同长度的前缀和后缀

直接将字符串相加

最后暴力枚举，记录答案

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int Base = 131;
unsigned long long p[200005], h1[200005], h2[200005];
unsigned long long H(int l, int r, int z){ //hash取值
	if(z == 1) {
		if(l == 0) return h1[r];
		return h1[r] - h1[l - 1] * p[r - l + 1];
	} else {
		if(l == 0) return h2[r];
		return h2[r] - h2[l - 1] * p[r - l + 1];
	}
}
string solve(string A, string B){
	h1[0] = (A[0] - 'a');
	for(int i = 1; i < A.size(); i++) {
		h1[i] = h1[i - 1] * Base + (A[i] - 'a');
	}
	h2[0] = (B[0] - 'a');
	for(int i = 1; i < B.size(); i++) {
		h2[i] = h2[i - 1] * Base + (B[i] - 'a');
	}
	if (B.size() <= A.size()){
		for(int i = 0; i < A.size() - B.size() + 1; i++) { //第一种和第二种情况
			if(H(i, i + B.size() - 1, 1) == H(0, B.size() - 1, 2)) {
				return A;
			}
		}
	}
	for(int i = min(A.size(), B.size()) - 1; i >= 1; i--) { //第三种情况，枚举相同子串长度 
		if(H(A.size() - i, A.size() - 1, 1) == H(0, i - 1, 2)) {
			string ans=A;
			for(int j = i; j < B.size(); j++){
				ans += B[j];
			}
			return ans;
		}
	}
	return A + B; //第四种情况
}
int main() {
	ios::sync_with_stdio(false);
	p[0] = 1; //初始化
	for(int i = 1; i <= 200000; i++) {
		p[i] = p[i - 1] * Base;
	}
	string s[3];
	cin >> s[0] >> s[1] >> s[2]; //输入
	int ans = INT_MAX;
	for(int i = 0; i < 3; i++) { //暴力枚举
		for(int j = 0; j < 3; j++) {
			for(int k = 0; k < 3; k++) {
				if(i != j && j != k && i != k) {
					ans = min(ans, min((int)solve(s[i], solve(s[j], s[k])).size(), (int)solve(solve(s[i], s[j]), s[k]).size())); //更新答案（这里把第一种和第二种写在一起了）
				}
			}
		}
	}
	cout << ans << endl; //输出
	return 0;
}
```


---

## 作者：Seanq (赞：4)

**CF25E Test 题解**  
大西北黑题开发集团推出  
考点：KMP  
题意自己理解  
每次将3个字符串重排，预处理出i,j之间的匹配关系，最后计算。  
具体代码里有！  
std:  
```cpp
#include<bits/stdc++.h>
using namespace std;
const int INF=2147483647;//定义无穷大 
int nxt[4][100001]={0};
bool ok[4];
void getnext(int m,char s2[],int t){//预处理s2的next数组 
    int j=0;
    for(int i=2;i<=m;i++){
        while(j!=0&&s2[j+1]!=s2[i])j=nxt[t][j];
        if(s2[j+1]==s2[i])j++;
        nxt[t][i]=j; 
    }
    return;
}
int KMP(int n,int m,char s1[],char s2[],int t){//KMP匹配s1,s2 
    int j=0,cnt=0;
    for(int i=1;i<=n;i++){
        while(j!=0&&s2[j+1]!=s1[i])j=nxt[t][j];
        if(s2[j+1]==s1[i])j++;
        if(j==m){
        return -1;
        j=nxt[t][j];
        }
    }
    return j;
}
char s[4][100001];
int len[4];
int K[4][4];
int main(){
    scanf("%s%s%s",s[1]+1,s[2]+1,s[3]+1);//输入字符串 
    len[1]=strlen(s[1]+1);//计算长度 
    len[2]=strlen(s[2]+1);
    len[3]=strlen(s[3]+1);
    for(int i=1;i<=3;i++){//next数组预处理 
    getnext(len[i],s[i],i);
    for(int j=1;j<=3;j++){//预处理匹配 
        if(i==j)continue;
        K[j][i]=KMP(len[j],len[i],s[j],s[i],i);
    }
    }
    int ans=INF;
    for(int i=1;i<=3;i++){//枚举顺序 
    for(int j=1;j<=3;j++){
        for(int k=1;k<=3;k++){
        if(i==j||j==k||i==k)continue;//不合法顺序，返回 
        int sum=len[i]+len[j]+len[k]-K[i][j]-K[j][k];//计算长度 
        if(K[i][j]>=0&&K[j][k]>=0)ans=min(ans,sum);//如果均不为子串 
        else{
            if(K[i][j]<0&&K[i][k]<0)ans=min(ans,len[i]);//若为子串 
            else if(K[i][j]<0)ans=min(ans,sum+K[i][j]+K[j][k]-len[j]-K[i][k]);//若j为i的子串 
            if(K[j][k]<0)ans=min(ans,sum+K[j][k]-len[k]);//若k为j的子串 
        }
        }
    }
    }
    printf("%d\n",ans);//愉快输出 
    return 0;
}
```

---

## 作者：happybob (赞：2)

考虑枚举三个字符串的全排列，设为 $x,y,z$。

分类讨论：

- 若 $y$ 是 $x$ 的子串：

 	- 若 $z$ 是 $x$ 的子串，最短的长度为 $x$ 的长度。
   - 否则找到 $z$ 的最长前缀，满足其是 $x$ 的后缀。
- 否则：

	- 找到 $y$ 的最长前缀，满足其是 $x$ 的后缀。
   - 设找到后拼起来的字符串为 $p$。讨论 $z$ 与 $p$ 的关系即可。
   
可以 KMP，也可以哈希。

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <cstdio>
using namespace std;
// 12323
const int N = 5e5 + 5;

using ull = unsigned long long;
string s[4];
int ans = 2e9;

ull powe[N], hash1[N], hash2[N], hash3[N], hash4[N];

int getans()
{
	hash1[0] = s[1][0] - 'a' + 1;
	hash2[0] = s[2][0] - 'a' + 1;
	hash3[0] = s[3][0] - 'a' + 1;
	for (int i = 1; i < s[1].size(); i++)
	{
		hash1[i] = hash1[i - 1] * 337 + (s[1][i] - 'a' + 1);
	}
	for (int i = 1; i < s[2].size(); i++)
	{
		hash2[i] = hash2[i - 1] * 337 + (s[2][i] - 'a' + 1);
	}
	for (int i = 1; i < s[3].size(); i++)
	{
		hash3[i] = hash3[i - 1] * 337 + (s[3][i] - 'a' + 1);
	}
	ull h1 = hash1[s[1].size() - 1], h2 = hash2[s[2].size() - 1], h3 = hash3[s[3].size() - 1];
	bool flag = 0;
	for (int i = 0; i + s[2].size() - 1 < s[1].size(); i++)
	{
		int l = i, r = i + s[2].size() - 1;
		ull subhash = hash1[r] - (l == 0 ? 0 : hash1[l - 1] * powe[r - l + 1]);
		if (subhash == h2)
		{
			flag = 1;
			break;
		}
	}
	if (flag)
	{
		bool flag2 = 0;
		for (int i = 0; i + s[3].size() - 1 < s[1].size(); i++)
		{
			int l = i, r = i + s[3].size() - 1;
			ull subhash = hash1[r] - (l == 0 ? 0 : hash1[l - 1] * powe[r - l + 1]);
			if (subhash == h3)
			{
				flag2 = 1;
				break;
			}
		}
		if (flag2) return s[1].size();
		int res = s[1].size() + s[3].size();
		for (int i = 1; i <= min(s[1].size(), s[3].size()); i++)
		{
			int l1 = 0, r1 = i - 1;
			int l2 = s[1].size() - i, r2 = s[1].size() - 1;
			ull hs1 = hash3[r1];
			ull hs2 = hash1[r2] - (l2 == 0 ? 0 : hash1[l2 - 1] * powe[r2 - l2 + 1]);
			if (hs1 == hs2) res = min(res, (int)(s[1].size() + s[3].size() - i));
		}
		return res;
	}
	else
	{
		string mn = s[1] + s[2];
		int res = s[1].size() + s[2].size();
		int p = 0;
		for (int i = 1; i <= min(s[1].size(), s[2].size()); i++)
		{
			int l1 = 0, r1 = i - 1;
			int l2 = s[1].size() - i, r2 = s[1].size() - 1;
			ull hs1 = hash2[r1];
			ull hs2 = hash1[r2] - (l2 == 0 ? 0 : hash1[l2 - 1] * powe[r2 - l2 + 1]);
			if (hs1 == hs2)
			{
				if ((int)(s[1].size() + s[2].size() - i) < res)
				{
					res = (s[1].size() + s[2].size() - i);
					p = i;
				}
			}
		}
		if (p)
		{
			mn = s[1].substr(0, s[1].size() - p) + s[2];
		}
		hash4[0] = mn[0] - 'a' + 1;
		for (int i = 1; i < mn.size(); i++)
		{
			hash4[i] = hash4[i - 1] * 337 + (mn[i] - 'a' + 1);
		}
		res = mn.size() + s[3].size();
		for (int i = 1; i <= min(mn.size(), s[3].size()); i++)
		{
			int l1 = 0, r1 = i - 1;
			int l2 = mn.size() - i, r2 = mn.size() - 1;
			ull hs1 = hash3[r1];
			ull hs2 = hash4[r2] - (l2 == 0 ? 0 : hash4[l2 - 1] * powe[r2 - l2 + 1]);
			if (hs1 == hs2)
			{
				res = min(res, (int)(mn.size() + s[3].size() - i));
			}
		}
		return res;
	}
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(nullptr);
	powe[0] = 1;
	for (int i = 1; i < N; i++)
	{
		powe[i] = powe[i - 1] * 337;
	}
	cin >> s[1] >> s[2] >> s[3];
	sort(s + 1, s + 4);
	int res = 1e9;
	do
	{
		res = min(res, getans());
	} while (next_permutation(s + 1, s + 4));
	cout << res << "\n";
	return 0;
}
```


---

## 作者：lalaouye (赞：2)

本题为 KMP 算法模板题。

## 思路

先想象把三个字符串并排放一起，此时我们发现我们的任务是尽可能重叠相邻字符串的后缀和前缀。

因为它只给 $3$ 个字符串，所以说我们甚至可以暴枚三个字符串的位置，然后互相跑 KMP 算法，求出每个字符串之间的最长后缀配前缀、最长前缀后缀再枚举即可 AC。

当然了，还要对两个字符串的包含关系进行处理。具体方法可看代码。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

char sa[N], sb[N], sc[N];
int nxta[N], nxtb[N], nxtc[N];
int a[4][4], b[4];

void getnxt (int len, char *str, int *nxt)
{
	int j = 0;
	for (int i = 2; i <= len; i ++)
	{
		while (j && str[i] != str[j + 1]) j = nxt[j];
		if (str[i] == str[j + 1]) j ++;
		nxt[i] = j;
	}
}

int KMP (int la, int lb, char *sta,char *stb, int *nxt)
{
	int j = 0;
	for (int i = 1; i <= la; i ++)
	{
		while (j && sta[i] != stb[j + 1]) j = nxt[j];
		if (sta[i] == stb[j + 1]) j ++;
		if (j == lb) return lb;//如果有被包含关系，那就返回长度，方便处理。 
		if (i == la) return j;
	}
}

int main ()
{
	scanf ("%s\n%s\n%s", sa + 1, sb + 1, sc + 1);
	int la = strlen (sa + 1), lb = strlen (sb + 1), lc = strlen (sc + 1);
	getnxt (la, sa, nxta);
	getnxt (lb, sb, nxtb);
	getnxt (lc, sc, nxtc);
	//枚举任意两个的最长重合前缀后缀。 a 数组表示最大的重叠关系，答案便是三个字符串的长度总和减去重叠数目。 
	a[1][2] = KMP (la, lb, sa, sb, nxtb);//sa 的后缀和 sb 的前缀 。 
	a[1][3] = KMP (la, lc, sa, sc, nxtc);//以此类推 。 
	a[2][1] = KMP (lb, la, sb, sa, nxta);
	a[2][3] = KMP (lb, lc, sb, sc, nxtc);
	a[3][1] = KMP (lc, la, sc, sa, nxta);
	a[3][2] = KMP (lc, lb, sc, sb, nxtb);
	//如果有包含关系，那就直接让关于这两个字符串的重叠数量全部为被包含字符串的长度。 
	for (int i = 1; i <= 3; i ++)
	{
		if (a[i][1] == la || a[1][i] == la) a[1][i] = a[i][1] = la;
		if (a[i][2] == lb || a[2][i] == lb) a[2][i] = a[i][2] = lb;
		if (a[i][3] == lc || a[3][i] == lc) a[3][i] = a[i][3] = lc;
	}
	int res = 0;
	res = max (res, max (a[1][2] + a[3][1], a[1][3] + a[2][1])); 
	res = max (res, max (a[2][1] + a[3][2], a[1][2] + a[2][3]));
	res = max (res, max (a[3][1] + a[2][3], a[1][3] + a[3][2]));
	printf ("%d\n", la + lb + lc - res);
	return 0;
}
```


---

## 作者：冷笑叹秋萧 (赞：2)

[题目传送门](https://codeforces.com/problemset/problem/25/E)
## 题意
给你三个字符串，问最短同时以这三个字符串为子串的字符串的长度是多少。

$s1,s2,s3≤10^{5}$
## 题解
观察题目数据范围，发现应该使要用 $O(|s|)$ 左右的时间复杂度解决此题。

可以发现显然有一个结论，就是当你确定了三个字符串放置的顺序，那么只需要将三个字符串接起来，然后将相邻两个字符串的最长相同前后缀只取一段即可。

对于这个问题，显然可以用**KMP**实现，但是可以用另一种简单易懂的方式处理子串问题，就是**字符串哈希**。

简述一下字符串哈希的过程：

设 $haxi[i]$ 表示字符串 $S$ 前 $i$ 位的哈希值，那么哈希公式如下：

$haxi[i]=(haxi[i-1] \cdot p+s[i])\bmod mo$

其中，$p$ 和 $mo$ 是两个质数， $mo>p$ 。

如果我们要提取一个子串 $s[l \sim r]$，那么公式为：

$haxi[l \sim r]=((haxi[r]-haxi[l] \cdot p ^ {r-l+1})\bmod mo+mo)\bmod mo$

然后特判一下当前要拼接的两个串是否是对方的字串，如果是的话直接舍弃字串即可。

当然可以使用双哈希减少冲突概率，简单来说就是使用两个模数，mo1和mo2，构造两个哈希数组(haxi1，haxi2)双保险。

关于质数的选取可以参考一下[这篇博客](https://blog.csdn.net/pengwill97/article/details/80879387)
## CODE

```cpp
#include<bits/stdc++.h>
#define LL long long
#define INF 0x3f3f3f3f
using namespace std;
const LL MO = 402653189, P = 131;
const int pl[6][3]={{0, 1, 2}, {0, 2, 1}, {1, 0, 2}, {1, 2, 0}, {2, 0, 1}, {2, 1, 0}}, N = 100005;
//懒得写递归，字符串排列顺序
int ans, len[3], sum;
char s[3][N];
LL haxi[3][N], mi[N];
bool pd(int lens, int lent, int k1, int k2) {
	if (lens > lent) {
		for (int i = 1; i <= lens - lent + 1; ++i) {
			int r = i + lent - 1;
			if (((haxi[k1][r] - haxi[k1][i - 1] * mi[r - i + 1] % MO) + MO) % MO == haxi[k2][lent]) return 1;
		}
	}
	else {
		for (int i = 1; i <= lent - lens + 1; ++i) {
			int r = i + lens - 1;
			if (((haxi[k2][r] - haxi[k2][i - 1] * mi[r - i + 1] % MO) + MO) % MO == haxi[k1][lens]) return 1;
		}
	} return 0;
}//判断是字串的情况
int solve(int lens, int lent, int k1, int k2) {
	for (int i = min(lens, lent); i; --i) {
		int l = lens - i + 1;
		if (((haxi[k1][lens] - haxi[k1][l - 1] * mi[lens - l + 1] % MO) % MO + MO) % MO == haxi[k2][i]) return i;
	} return 0;
}//找最长相同前后缀
int main() {
	mi[0] = 1; ans = INF;
	for (int i = 1; i < N; ++i) mi[i] = mi[i - 1] * P % MO;//预处理幂会更快
	for (int i = 0; i < 3; ++i) {
		scanf("%s", s[i] + 1); len[i] = strlen(s[i] + 1); sum += len[i];
		for (int j = 1; j <= len[i]; ++j) haxi[i][j] = (haxi[i][j - 1] * P + s[i][j]) % MO;//字符串哈希
	}
	for (int i = 0; i < 6; ++i) {
		int res = 0;
		for (int j = 1; j < 3; ++j) {
			if (pd(len[pl[i][j]], len[pl[i][j - 1]], pl[i][j], pl[i][j - 1])) {
				res += min(len[pl[i][j]], len[pl[i][j - 1]]); continue;
			} res += solve(len[pl[i][j]], len[pl[i][j - 1]], pl[i][j],pl[i][j - 1]);
		} ans = min(ans, sum - res);
	} printf("%d\n",ans);
	return 0;
}
```


---

## 作者：Richard_Whr (赞：2)

来一发不动脑子的题解：

看到多串啥都不想直接上 AC 自动机。

这玩意甚至比 kmp 还要简单，增量构造就是香。

然后经典的一个串的多串匹配看成在节点上跳来跳去。

如何处理 $3$ 串都有呢，注意到数字非常小，直接一波状压。

搞个类似分层图的东西，最后发现边权只有 $1$，那就 bfs 好了。

常数略大，不过仍是线性，从思路到实现都非常简单。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+10,M=26;
typedef pair<int,int> PII;
int tr[N][M],ne[N],idx;
int id[N],q[N];

void insert(int x,char s[])
{
	int u=0;
	for(int i=0;s[i];i++)
	{
		int c=s[i]-'a';
		if(!tr[u][c]) tr[u][c]=++idx;
		u=tr[u][c];
	}
	id[u]|=(1<<x);
}
void build()
{
	int hh=0,tt=-1;
	for(int c=0;c<M;c++) if(tr[0][c]) q[++tt]=tr[0][c];
	while(hh<=tt)
	{
		int t=q[hh++];
		for(int c=0;c<M;c++)
		{
			int u=tr[t][c];
			if(!u) tr[t][c]=tr[ne[t]][c];
			else ne[u]=tr[ne[t]][c],q[++tt]=u;
		}
		id[t]|=id[ne[t]];
	}
}
int dist[N][10];
bool st[N][10];
PII que[N*10];
int bfs()
{
	int hh=0,tt=-1;
	memset(dist,0x3f,sizeof dist);
	dist[0][0]=0,que[++tt]={0,0},st[0][0]=true;

	while(hh<=tt)
	{
		auto t=que[hh++];
		int u=t.first,state=t.second;
		for(int c=0;c<26;c++)
		{
			int v=tr[u][c];
			if(!st[v][state|id[v]])
			{
				st[v][state|id[v]]=true;
				dist[v][state|id[v]]=dist[u][state]+1;
				que[++tt]={v,state|id[v]};
			}
		} 
	}
	
	int res=0x3f3f3f3f;
	for(int i=0;i<=idx;i++) res=min(res,dist[i][7]);
	return res;
}

char s[N];

signed main()
{
	for(int i=0;i<3;i++)
	{
		cin>>s;
		insert(i,s);
	}
	
	build();
	
	cout<<bfs()<<"\n";
	
	return 0;
}
```


---

## 作者：Acerkaio (赞：0)

[题面](https://www.luogu.com.cn/problem/CF25E)
## ~~暴力思路清晰~~

## 0x001 思路

由于只有三个串，不考虑包含关系的话，就全排列去暴力排序。

只要用 `next_permutation` 函数就好了，函数执行下一次排列，具体用法详见代码。

然后合并两个序列，即：将相同的前一个序列的后缀与后一个序列的前缀的部分去掉其中一个，拼接序列。这样是 $O(nm)$ 的，显然不优，考虑使用更优的方法。

我们发现，在拼接序列时，可以更优。我们把拼接的两个序列反个顺序直接拼接，这时候，这个序列的最长公共前缀后缀就是我们原来拼接可以消除的那一段。

好诶，接下来就简单了（~~暴力去搞就好了~~

## 0x002 CODE

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int border[500007], answer = 0x7fffffff;
void find_border(string ee) {
	int j = 0, len = ee.size();
	ee = " " + ee;
	for (int i = 2; i <= len; i++) {
		while (j && ee[j + 1] != ee[i]) j = border[j];
		if (ee[j + 1] == ee[i]) j++;
		border[i] = j;
	}
	return ;
}
bool kmp(string a, string b) {
	find_border(b);
	int j = 0, len = a.size(), lenb = b.size();
	a = " " + a;
	b = " " + b;
	for (int i = 2; i <= len; i++) {
		while (j && a[i] != b[j + 1]) j = border[j];
		if (a[i] == b[j + 1]) j++;
		if (j == lenb) return true;
	}
	return false;
}
string put(string a, string b) {
	if (a.size() < b.size()) {
		if (kmp(b, a)) return b;
	} else {
		if (kmp(a, b)) return a;
	}
	string tpa = b + a;
	find_border(tpa);
	//cout << tpa << '\n';
	int l = border[tpa.size()];
	string tpb = "";
	for (int i = l; i < b.size(); i++)
		tpb += b[i];
	return a + tpb;
}
void get(string a, string b, string c) {
	answer = min(answer, (long long)put(put(a, b), c).size());
}
signed main() {
	string a[3];
	cin >> a[0] >> a[1] >> a[2];
	int num[3]{0, 1, 2};
	do{
		get(a[num[0]], a[num[1]], a[num[2]]);
	} while (next_permutation(num, num + 3));
	cout << answer << '\n';
	return 0;
}
```


---

## 作者：Chthologist7507 (赞：0)

双倍经验：SP7155，改成多组输入即可 

前置知识：kmp，可左转 P3375

题意即求最短的使 $s1,s2,s3$ 均为其子串的字符串 $s$

很明显，字符串长度最大值就是三子串长度之和

然后考虑重合情况

-----------

化归：考虑两个子串，再考虑三个子串的情况

不妨先求最短的使 $s1,s2$ 均为其子串的字符串 $ss$

两个子串仅有 $3$ 种情况：（不妨假设 $s1$ 的长度大于等于 $s2$，这里顺便借用一下两圆的关系）

- 相离，例如 $abccd$ 和 $bddc$，此时 $s=s1+s2$

- 相交，例如 $abccd$ 和 $bccde$，此时 $s=s1+s2-s1\cap s2$

- 包含，例如 $abccd$ 和 $bcc$，此时 $s=s1$

其中 $s1\cap s2$ 拿 kmp 乱搞一下就行了，求匹配结束后 $s2$ 的指针所在位置

-----------

三个子串怎么办？

可以先求 $ss$，再求最短的使 $ss,s3$ 均为其子串的字符串，然后将 $s2,s3$ 互换，重来，再将 $s1,s3$ 互换，再来一次


也可以分多类讨论，也不难

最后献上分类讨论的代码：

```cpp
#include<bits/stdc++.h>
#define inl inline 
#define rep(i,a,b) for(int i=(a),i##end=(b);i<=i##end;i++)
#define pre(i,a,b) for(int i=(a),i##end=(b);i>=i##end;i--)
using namespace std;
const int N=1e6+10;
int pmt[N][4];//pmt 数组，就可以看做是整体前移的 next 数组
void get_pmt(const string &s,int t){
	for(int i=1,j=0;i<s.size();++i){
		while(j&&s[i]!=s[j])j=pmt[j-1][t];
		if(s[i]==s[j])j++;
		pmt[i][t]=j;
	}
}
int kmp(string s,string p,int t1,int t2){
//	if(s.size()<p.size()){swap(s,p);swap(t1,t2);}
	int j=0;
	for(int i=0;i<s.size();i++){
		while(j&&s[i]!=p[j])j=pmt[j-1][t2];
		if(s[i]==p[j])j++;
		if(j==p.size())return -1;
	}
	return j;
}
string s[4];
int km[4][4];
signed main(void){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>s[1]>>s[2]>>s[3];
    get_pmt(s[1],1);get_pmt(s[2],2);get_pmt(s[3],3);
    km[1][2]=kmp(s[1],s[2],1,2);
    km[2][1]=kmp(s[2],s[1],2,1);
    km[1][3]=kmp(s[1],s[3],1,3);
    km[3][1]=kmp(s[3],s[1],3,1);
    km[2][3]=kmp(s[2],s[3],2,3);
    km[3][2]=kmp(s[3],s[2],3,2);//这里注意：km[a][b]!=km[b][a]，因为 km 第一维表示“文本串”，第二维则是“模式串”
    int ans=0x3f3f3f3f;
    rep(i,1,3)rep(j,1,3)rep(k,1,3){
        if(i==j||j==k||i==k)continue; //只有两两不同才有意义
        int sum=s[i].size()+s[j].size()+s[k].size()-km[i][j]-km[j][k]; //这里说下分多类讨论的写法
        if(km[i][j]>=0&&km[j][k]>=0)ans=min(ans,sum); //如果不存在包含关系，那么 sum 即为所求
        else{
            if(km[i][j]<0&&km[i][k]<0)ans=min(ans,(int)s[i].size()); //存在一个大串使得其他两个小串均为其子串，那么大串长度即为所求
            else if(km[i][j]<0)ans=min(ans,sum+km[i][j]+km[j][k]-(int)s[j].size()-km[i][k]);//sj 是 si 子串，那么不考虑 sj，化为两子串的问题 
            if(km[j][k]<0)ans=min(ans,sum+km[j][k]-(int)s[k].size()); //sk 是 sj 子串，那么不考虑 sk，化为两子串的问题 
        }
    }
    cout<<ans<<'\n';
}
```

---

