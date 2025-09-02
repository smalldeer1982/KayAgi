# CF25E - Test

## 题目描述

### 题目翻译

Bob 出了一道字符串题，题目的输入是一个字符串。

毒瘤的 Bob 写了 $3$ 个程序，但他发现了一个悲剧：

1. 当输入的字符串有子串 $s_1$ 时，程序 $1$ 会 WA；

1. 当输入的字符串有子串 $s_2$ 时，程序 $2$ 会死循环；

1. 当输入的字符串有子串 $s_3$ 时，程序 $3$ 会 MLE。

当然，可以假定其他情况下程序不会出锅。

Bob 非常毒瘤，他想找一个最短的输入字符串 $ss$，使得 $3$ 个程序都过不了。请输出最小的长度。

## 样例 #1

### 输入

```
ab
bc
cd
abacaba
abaaba
x
```

### 输出

```
4
11
```

# 题解

## 作者：hnzzlxs01 (赞：8)

**双倍经验：[CF25E](https://www.luogu.com.cn/problem/CF25E)**

**前置芝士：[KMP算法](https://www.luogu.com.cn/problem/P3375)**

对于这道题，其实质就是求一个最短的字符串的长度，其子串包含 $s_1$，$s_2$，和 $s_3$。如何求呢？

思路：求这个字符串，可以考虑先求 **$s_1$ 的后缀和 $s_2$ 的前缀** 的最长相等子串，借此得到 $s_1$ 加上删去相等前缀的 $s_2$ 的 $s$，再求 **$s$ 的后缀和 $s_3$ 的前缀** 的最长相等字串，再借此得到 $s$ 加上删去相等前缀的 $s_3$ 的最终的 $s$，最后返回 $s$ 的长度就是答案。

~~有点懵？~~ 没事，上样例：

```
abacaba
abaaba
x
```

先考虑只有 $s_1$，$s_2$ 的情况，求出 $s_1$，$s_2$ 的 $s$ 后将 $s$ 作为 $s_1$，$s_3$ 作为 $s_2$ 再求一遍即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/egpt2btw.png)

不难发现，此时 $s_1$、$s_2$ 拼接的最优解 $s$ 就是找到 $s_1$ 和 $s_2$ 的相等前后缀，**将 $s_1$ 后接上 $s_2$ 删去相等前缀** 的部分。

$s$ 和 $s_3$ 同理：
 
![](https://cdn.luogu.com.cn/upload/image_hosting/lj0nyoov.png)

此时 $s$ 和 $s_3$ 没有相等的前后缀，因此将 $s_3$ 接在 $s$ 后就得到了最终的 $s$。

到这里有的同学可能会有疑问：如果输入顺序是
```
abacaba
x
abaaba
```
那么得到的 $s$ 就是 `abacabaxabaaba` 了，答案不就是 $14$ 了吗？

这个问题很好。再次仔细看题，发现
```
每组数据 3 行，每行一个字符串，分别代表 s1,s2,s3，只含小写字母。
```
只有 $s_1$、$s_2$ 和 $s_3$ 三个字符串，所以我们完全可以枚举 $s_1$、$s_2$ 和 $s_3$ 每一种可能的排列情况，再对结果取 $\min$ 得到最终答案！

还有一点：如果数据为
```
abaefdaba
efd
aba
```
的话，按我们的程序，会由于忽略了 $s_1$ 中已经包含了 $s_2$ 而导致错误的答案。

因此我们可以在查找最长相等前后缀前**先判断 $s_1$ 中是否包含** $s_2$ 来避开这种情况。$s$ 和 $s_3$ 同理。

那么如何求这个 $s$ 并且查找 $s1$ 中是否包含 $s2$ 呢？**KMP！**

在 KMP 算法的 $next$ 数组中，$next_i$ 保存了当前字符串从第 $0$ 位到第 $i$ 位的最大相等前后缀长度，我们则可以利用这个 $next_i$。

定义一个字符串 $sl$，令
```cpp
sl = s2 + "@" + s1;
```

求出 $sl$ 的 $next$ 数组，令 $maxx$ （初始值为 $0$ ） 等于 $maxx$ 和 `next[sl.size() - 1]` 的最大值。

下一步的 $s$ 和 $s_3$ 同理。

对于查找 $s_1$ 中是否包含 $s_2$，可以直接用 KMP 算法来查找。

**最后贴代码：**
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 100005 * 3;
string s1, s2, s3;
int vnext[maxn];
void getnext(string s) {
    int j = 0;
    int len = s.size();
    vnext[0] = 0;
    for (int i = 1; i < len; i++) {
        while (j > 0 && s[i] != s[j]) j = vnext[j - 1];
        if (s[i] == s[j]) {
            j++;
        }
        vnext[i] = j;
    }
}
bool find(string s1, string s2) {
// 查在s1中是否存在s2
    int ne[maxn];
    memset(ne, 0, sizeof(ne));
    int j = 0;
    int len1 = s1.size(), len2 = s2.size();
    for (int i = 0; i < len1; i++) {
        while (j > 0 && s1[i] != s2[j]) j = ne[j - 1];
        if (s1[i] == s2[j]) j++;
        if (j == len2) return 1;
    }
    return 0;
}
int getans(string s1, string s2, string s3) {
    string s = s1;
    string sl, ss;
    int maxx = 0;
    if (!find(s, s2)) {
    // 查在s1中是否存在s2
        sl = s2 + "@" + s;
        getnext(sl);
        maxx = max(maxx, vnext[sl.size() - 1]);
        if (maxx == 0) s += s2;// 无相等前后缀
        else {// 存在相等前后缀
            ss = s2.substr(maxx, s2.size() - maxx + 1);
            // 截取s2删去相等前缀的部分
            s += ss;
            // 得到第一个s
        }
    }
    if (!find(s, s3)) {
    // 查在s中是否存在s3
        memset(vnext, 0, sizeof(vnext));
        sl = s3 + "@" + s;
        getnext(sl);
        maxx = 0;
        maxx = max(maxx, vnext[sl.size() - 1]);
        if (maxx == 0) s += s3;// 无相等前后缀
        else {// 存在相等前后缀
            ss = s3.substr(maxx, s3.size() - maxx + 1);
            // 截取s3删去相等前缀的部分
            s += ss;
            // 得到最终的s
        }
    }
    return s.size();// 返回答案
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    while (cin >> s1 >> s2 >> s3) {
        int ans = 0x3f3f3f3f;
        // 枚举s1、s2、s3的每一种排列情况
        ans = min(ans, getans(s1, s2, s3));
        ans = min(ans, getans(s1, s3, s2));
        ans = min(ans, getans(s2, s1, s3));
        ans = min(ans, getans(s2, s3, s1));
        ans = min(ans, getans(s3, s1, s2));
        ans = min(ans, getans(s3, s2, s1));
        cout << ans << "\n";
    }
    return 0;
}
```

---

## 作者：NekoPass (赞：8)

### Click [Here](https://www.luogu.org/blog/NekoPass/solution-cf25e) For Better Experience
### 这道题只是CF25E的SPJ，所以只要改一下就好了喵
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
    while(scanf("%s%s%s",s[1]+1,s[2]+1,s[3]+1)==3){
    //当然，也可以使用while(cin>>s[1]+1>>s[2]+1>>s[3]+1) 不过会慢一些
    int ans=INF;
    l[1]=strlen(s[1]+1);l[2]=strlen(s[2]+1);l[3]=strlen(s[3]+1);
    Pre();
    ans=min(ans,f(1,2,3));ans=min(ans,f(1,3,2));
    ans=min(ans,f(2,1,3));ans=min(ans,f(2,3,1));
    ans=min(ans,f(3,2,1));ans=min(ans,f(3,1,2));
    //真·暴力枚举排列顺序 
    printf("%d",ans);//快乐AC喵(OωO)}
    return 0;
}
```
### 真的不来nekopass的[喵窝](https://www.luogu.org/blog/NekoPass/)看看喵？

---

## 作者：chufuzhe (赞：3)

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
   while(cin >> s[0] >> s[1] >> s[2]) {//输入
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
	}
	return 0;
}
```


---

## 作者：Chthologist7507 (赞：1)

双倍经验：CF25E 

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
	while(cin>>s[1]>>s[2]>>s[3]){
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
}
```

---

## 作者：Seanq (赞：1)

**SP7155 CF25E - Test 题解**  
和CF25E Test一毛一样（除了多数据）  
不用担心，就是把CF25E的所有数据点并到了一起。  
(复制粘贴一下~)  


------------

大西北黑题开发集团推出
考点：KMP
题意自己理解
每次将3个字符串重排，预处理出i,j之间的匹配关系，最后计算。
具体代码里有！
std: 
```cpp
大西北黑题开发集团推出
考点：KMP
题意自己理解
每次将3个字符串重排，预处理出i,j之间的匹配关系，最后计算。
具体代码里有！
std: 
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
    while(scanf("%s%s%s",s[1]+1,s[2]+1,s[3]+1)==3){//多数据 
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
    }
    return 0;
}
```

---

