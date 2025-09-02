# Debate

## 题目描述

Elections in Berland are coming. There are only two candidates — Alice and Bob.

The main Berland TV channel plans to show political debates. There are $ n $ people who want to take part in the debate as a spectator. Each person is described by their influence and political views. There are four kinds of political views:

- supporting none of candidates (this kind is denoted as "00"),
- supporting Alice but not Bob (this kind is denoted as "10"),
- supporting Bob but not Alice (this kind is denoted as "01"),
- supporting both candidates (this kind is denoted as "11").

The direction of the TV channel wants to invite some of these people to the debate. The set of invited spectators should satisfy three conditions:

- at least half of spectators support Alice (i.e. $ 2 \cdot a \ge m $ , where $ a $ is number of spectators supporting Alice and $ m $ is the total number of spectators),
- at least half of spectators support Bob (i.e. $ 2 \cdot b \ge m $ , where $ b $ is number of spectators supporting Bob and $ m $ is the total number of spectators),
- the total influence of spectators is maximal possible.

Help the TV channel direction to select such non-empty set of spectators, or tell that this is impossible.

## 说明/提示

In the first example $ 4 $ spectators can be invited to maximize total influence: $ 1 $ , $ 2 $ , $ 3 $ and $ 6 $ . Their political views are: "11", "10", "01" and "00". So in total $ 2 $ out of $ 4 $ spectators support Alice and $ 2 $ out of $ 4 $ spectators support Bob. The total influence is $ 6+4+3+9=22 $ .

In the second example the direction can select all the people except the $ 5 $ -th person.

In the third example the direction can select people with indices: $ 1 $ , $ 4 $ , $ 5 $ and $ 6 $ .

In the fourth example it is impossible to select any non-empty set of spectators.

## 样例 #1

### 输入

```
6
11 6
10 4
01 3
00 3
00 7
00 9
```

### 输出

```
22
```

## 样例 #2

### 输入

```
5
11 1
01 1
00 100
10 1
01 1
```

### 输出

```
103
```

## 样例 #3

### 输入

```
6
11 19
10 22
00 18
00 29
11 29
10 28
```

### 输出

```
105
```

## 样例 #4

### 输入

```
3
00 5000
00 5000
00 5000
```

### 输出

```
0
```

# 题解

## 作者：bzzltl (赞：3)

## 题目大意

有 $2$ 个候选人（分别设为 $A$ 和 $B$），$n$ 个可以发表见解的旁观者，每个旁观者有各自的看法和影响力。

旁观人一共有 $4$ 种看法，第一种是既支持 $A$ 也支持 $B$，第二种是只支持 $A$ ，第三种是只支持 $B$ ，第四种是谁也不支持。

我们从 $n$ 个人中选择任意人数。为了让争论更加激烈，需要满足 $A$ 的支持者和 $B$ 的支持者各自的人数都比总数的二分之一还要大这一条件。

在满足这一条件的情况下，需要让节目的影响力尽量大。

节目的影响力为各个被选中的人的影响力之和。

## 大致思路

贪心。

### 情况一

首先，如果一个人 $A$ 和 $B$ 都支持的话，不论他的影响力是多少，邀请他肯定不会使结果更劣，所以我们可以很放心地将他纳入答案。


### 情况二
若是一个人只支持 $A$ 的话，那么我们就需要考虑一下了，如果还有人只支持 $B$ 的人可以和他配对的话的话，我们就可以将他们一起选入，这样不会不满足条件，证明如下（举 $A$ 的人数变化为例）：

设 $a$ 为此时已经选上了的支持 $A$ 的人数， $b$ 为此时已经选上了的支持 $B$ 的人数， $c$ 为已经选上的人的总人数，则显然此时

$$\dfrac{a}{c}\geq \dfrac{1}{2}$$

易得：

$$a\geq \dfrac{c}{2}$$

当把 $a$、$b$ 都选上,原式推得：

$$\dfrac{a+1}{c+2}\geq \dfrac{\dfrac{c}{2}+1}{c+2}\geq \dfrac{\dfrac{c+2}{2}}{c+2}\geq \dfrac{1}{2}$$

当且仅当 $a=\dfrac{c}{2}$ 时，等式成立。

$B$ 的变化同理。

所以说，遇到可以配对的人的时候，可以直接将他们加入答案，并不会影响条件。

### 情况三

最后处理谁都不支持的，和剩下的只支持 $A$ （或者 $B$）的人。此时，无论是谁加入都可能会导致条件不成立，因此我们将谁都不支持的，和剩下的只支持 $A$ （或者 $B$）的人用一个数组存起来，再从大到小排序，根据影响力来选择，知道将要不满足条件为止。

## AC 代码

```cpp
#include<bitsdc++.h>
using namespace std;
const long long LLM=9e18+7;
const int IM=2e9+7;
const int N=4e5+7;
inline int read(){int x=0,y=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-') y=-y;c=getchar();}while(c>='0'&&c<='9'){x=x*10+(c^'0');c=getchar();}return x*y;}

int n,ans,cnt[4];
int jl1,jl2,jl0;
char s[3];
int t10[N],t01[N],t00[N];

bool cmp(int a,int b){return a>b;}

signed main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		cin>>s;
		int res=read(),p;
		if(s[0]-'0'&&s[1]-'0') ans+=res,p=3;
		else if(s[0]-'0') t10[++jl1]=res,p=1;
		else if(s[1]-'0') t01[++jl2]=res,p=2;
		else t00[++jl0]=res,p=0;
		cnt[p]++;
	}
	sort(t10+1,t10+jl1+1,cmp);
	sort(t01+1,t01+jl2+1,cmp);
	int mn=min(jl1,jl2);
	for(int i=1;i<=mn;i++) ans+=t01[i]+t10[i];
	int mu=(cnt[0]+mn)*2;
	int zi=cnt[3];
	for(int i=mn+1;i<=max(jl1,jl2);i++) t00[++jl0]=jl1>jl2?t10[i]:t01[i];
	sort(t00+1,t00+n+1,cmp);
	for(int i=1;i<=cnt[3];i++) ans+=t00[i];
	printf("%d\n",ans);
	return 0;
}

```

---

## 作者：是个汉子 (赞：2)

[原题](https://www.luogu.com.cn/problem/CF1070F)

### Solution

考虑贪心。

那么 $s_i=11$ 的肯定都选，因为这样不会使答案变劣



重点就是 $10,01,00$ 之间怎么选

首先， $00$ 肯定是最劣的，所以先考虑 $01,10$ 。

有一个结论是：在最优情况， $s_i=01$ 全部选出，或者 $s_i=10$ 全部选出

证明：设现在选了 $x$ 个 $01$ 的， $y$ 个 $10$ 的，那么再选 $\min(x,y)$ 个 $01$ 和 $10$ 显然是不会超过限制的。



按照 $s_i=10$ 全部选择，然后考虑剩下的 $01,00$ 

因为要最大，即贪心。所以要按照 $a_i$ 排序，然后枚举 $s_i=01$ 的选择个数 $j$ 。

当 $num_{11}+j<num_{10}$ 即支持Bob的人太少，或 $num_{11}+num_{10}<j$ 即支持Alice的人太少，就跳过这个 $j$ 

那么剩下的可选的就只有 $s_i=00$ 的，数量为 $\min\{num_{00},num_{11}+j-num_{10},num_{11}+num_{10}-j\}$ 个

其中第一个是 $s_i=00$ 初始数量，第二个是最多还有多少人能不支持Bob，第三个是最多还有多少人能不支持Alice

而 $s_i=01$ 同理即可

而枚举时候的价值可以拿前缀和优化，达到 $O(n\log n)$ 的时间复杂度。

### Code

```c++
#include<bits/stdc++.h>

using namespace std;
const int N=4e5+10;
int n,num[5],a[5][N],cnt,sum,ans;

inline bool cmp(const int &a,const int &b){
    return a>b;
}

int main(){
    scanf("%d",&n);
    for(int i=1,x,y;i<=n;i++){
        scanf("%d%d",&x,&y);
        if(!x) a[0][++num[0]]=y;
        else if(x==1) a[1][++num[1]]=y;
        else if(x==10) a[2][++num[2]]=y;
        else a[3][++num[3]]=y,sum+=y;
    }
    sort(a[0]+1,a[0]+num[0]+1,cmp);
    sort(a[1]+1,a[1]+num[1]+1,cmp);
    sort(a[2]+1,a[2]+num[2]+1,cmp);
    for(int i=2;i<=num[0];i++) a[0][i]+=a[0][i-1];
    for(int i=2;i<=num[1];i++) a[1][i]+=a[1][i-1];
    for(int i=2;i<=num[2];i++) a[2][i]+=a[2][i-1];
    for(int i=0;i<=num[1];i++){
        if(num[3]+i<num[2]||num[3]+num[2]<i) continue;
        ans=max(ans,a[1][i]+a[2][num[2]]+a[0][min(num[0],min(num[3]+i-num[2],num[3]+num[2]-i))]);
    }
    for(int i=0;i<=num[2];i++){
        if(num[3]+i<num[1]||num[3]+num[1]<i) continue;
        ans=max(ans,a[2][i]+a[1][num[1]]+a[0][min(num[0],min(num[3]+i-num[1],num[3]+num[1]-i))]);
    }
    printf("%d\n",ans+sum);
    return 0;
}
```

我这里把 $00,01,10,11$ 看作二进制了，心领神会吧(oﾟvﾟ)ノ

---

## 作者：Tjaweiof (赞：1)

# CF1070F 题解
[题目传送门](https://www.luogu.com.cn/problem/CF1070F)

把所有支持 Alice 和 Bob 的人找出来，如果一个人支持 Alice 和 Bob，那么答案可以直接加上这个人的影响力。一个仅支持 Alice 的人和一个仅支持 Bob 的人，称为一个小组，找出所有这样的小组，答案加上他们的影响力之和。剩下的从大到小排序，一个一个加，加到不满足条件为止。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[400001], b[400001], c[400001], d[400001], tot1, tot2, tot3, tot4, ans;
string s;
bool cmp(int x, int y){
	return x > y;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++){
		cin >> s;
		if (s == "00"){
			cin >> a[++tot1];
		} else if (s == "01"){
			cin >> b[++tot2];
		} else if (s == "10"){
			cin >> c[++tot3];
		} else {
			cin >> d[++tot4];
		}
	}
	sort(b + 1, b + tot2 + 1, cmp);
	sort(c + 1, c + tot3 + 1, cmp);
	sort(d + 1, d + tot4 + 1, cmp);
	for (int i = 1; i <= tot4; i++){
		ans += d[i];
	}
	for (int i = 1; i <= min(tot2, tot3); i++){
		ans += b[i] + c[i];
	}
	if (tot2 < tot3){
		for (int i = tot2 + 1; i <= tot3; i++){
			a[++tot1] = c[i];
		}
	} else {
		for (int i = tot3 + 1; i <= tot2; i++){
			a[++tot1] = b[i];
		}
	}
	sort(a + 1, a + tot1 + 1, cmp);
	for (int i = 1; i <= tot4; i++){
		ans += a[i];
	}
	cout << ans << endl;
	return 0;
}

```

---

## 作者：青烟绕指柔 (赞：1)

我们可以发现，拿状态为"11"，的就是白拿，因为权值都为正，所以肯定拿。

其次，对于状态"10"和"01"，一起拿，也是不影响的。所有直接拿。

然后就剩下"00"和"10"或者"00"和"01"，选最大的,状态"11"的个数。

AC代码：
```c
#pragma GCC optimize("-Ofast","-funroll-all-loops")
#include<bits/stdc++.h>
//#define int long long
using namespace std;
const int N=4e5+10;
int n,cnt,res; string str;
priority_queue<int> q[4],pq;
signed main(){
	cin>>n;
	for(int i=1,x,s;i<=n;i++){
		x=0;	cin>>str>>s;
		for(int j=0;j<2;j++)	if(str[j]=='1')	x|=(1<<j);	q[x].push(s);
	}
	while(q[3].size())	cnt++,res+=q[3].top(),q[3].pop();
	while(q[2].size()&&q[1].size())	res+=q[2].top()+q[1].top(),q[1].pop(),q[2].pop();
	for(int i=0;i<=2;i++)	while(q[i].size())	pq.push(q[i].top()),q[i].pop();
	while(cnt&&pq.size())	res+=pq.top(),cnt--,pq.pop();
	cout<<res;
	return 0;
}

```

---

## 作者：zxcdxw (赞：0)

本题的核心是**贪心**。

所以先  sort  一下。

通过支持两人中人数的较小者来决定总人数，为了满足条件两个人都支持的肯定要选。

接下来就是选择支持的人数使他们满足条件，因为已经  sort  过了，所以此时选择的一定是最优的。

话不多说上代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1e6 + 9;
struct debate {
	string a;
	int b;
}w[N];
bool cmp(debate a1, debate a2) {
	return a1.b > a2.b;
}
bool flag[N];
int main() {
	int n; cin >> n;
	int ans1 = 0, ans2 = 0;
	for (int i = 1; i <= n; ++i) {
		cin >> w[i].a >> w[i].b;
		if (w[i].a[0] == '1') ++ans1;
		if (w[i].a[1] == '1') ++ans2;
	}
	sort(w + 1, w + n + 1, cmp);
	int k;
	if (ans1 > ans2) k = 1;
	else k = 2;
	ll sum = 0;
	int cnt1 = 0, cnt2 = 0, cnt3 = 0;
	for (int i = 1; i <= n; ++i) {
		if (w[i].a[0] == '1' && w[i].a[1] == '1')
			sum += w[i].b, flag[i] = true, ++cnt3;
	}
	for (int i = 1; i <= n; ++i) {
		if (k == 1&&!flag[i]) {
			if (w[i].a[0] == '1' && cnt1+cnt3 < ans2)
				cnt1++, sum += w[i].b, flag[i] = true;
			if (w[i].a[1] == '1' && cnt2+cnt3 < ans2)
				cnt2++, sum += w[i].b, flag[i] = true;
		 
		}
		if (k == 2&&!flag[i]) {
			if (w[i].a[0] == '1' && cnt1+cnt3 < ans1)
				cnt1++, sum += w[i].b, flag[i] = true;
			if (w[i].a[1] == '1' && cnt2+cnt3 < ans1)
				cnt2++, sum += w[i].b, flag[i] = true;
		}
	}
	int cnt = 2 * min(ans1, ans2) - cnt1 - cnt2-cnt3;
	for (int i = 1, j = 0; j < cnt && i <= n; ++i) {
		if (flag[i]) continue;
		sum += w[i].b;
		++j;
	}
	cout << sum;
}
```



---

## 作者：不存在之人 (赞：0)

## 思路：

### 先把11的选上，然后01和10的选min(投01和10的人的个数），最后计算是否还可以再选入，然后从剩下的人当中选择影响力大的。
```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;
const int MAXN=1e6;
struct A
{
    int a,b=0;//这里可以用int型存储，比较方便
}s10[MAXN],s01[MAXN],s00[MAXN];
bool cmp(A x,A y)
{
    return x.b>y.b;
}
int main()
{
    int n,ans=0;
    cin>>n;
    int e11=0,e10=0,e01=0,e00=0;
    for(int i=0;i<n;i++)
    {
        int x,y;
        cin>>x>>y;
        if(x==11)
        {
            ans+=y;e11++;//投11的人一定会被选上，所以只需要记下影响力和人数就可以了
        }
        if(x==10)
        {
            s10[e10].a=x;s10[e10].b=y;e10++;
        }
        if(x==1)
        {
            s01[e01].a=x;s01[e01].b=y;e01++;
        }
        if(x==0)
        {
            s00[e00].a=x;s00[e00].b=y;e00++;
        }
    }
    sort(s10,s10+e10,cmp);//先对s01和s10按影响力从大到小排序
    sort(s01,s01+e01,cmp);
    int minn=min(e01,e10);   
    for(int i=0;i<minn;i++)
    {
        ans+=s10[i].b+s01[i].b;
    }
    int all=(e11+minn)*2;//计算可以选上的总人数
    int k=all-e11-minn*2;//k为还可以选的人数
    if(e10>e01)
    {
        for(int i=minn;i<e10;i++)//把s01或者s10中剩余的人数加到s00中，方便排序
            s00[e00++]=s10[i];
    }
    else
    {
        for(int i=minn;i<e01;i++)
            s00[e00++]=s01[i];
    }
    sort(s00,s00+e00,cmp);//此时s00中还存有s10或s01中剩余的人，然后排序
    for(int i=0;i<k;i++)
    {
        ans+=s00[i].b;//不需要考虑怎么投的票了，只需要选择影响力大的就可以了
    }
    cout<<ans<<endl;
    return 0;
}
```

---

