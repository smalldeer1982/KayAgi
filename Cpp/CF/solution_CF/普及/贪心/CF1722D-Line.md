# Line

## 题目描述

There are $ n $ people in a horizontal line, each looking either to the left or the right. Each person counts the number of people in the direction they are looking. The value of the line is the sum of each person's count.

For example, in the arrangement LRRLL, where L stands for a person looking left and R stands for a person looking right, the counts for each person are $ [0, 3, 2, 3, 4] $ , and the value is $ 0+3+2+3+4=12 $ .

You are given the initial arrangement of people in the line. For each $ k $ from $ 1 $ to $ n $ , determine the maximum value of the line if you can change the direction of at most $ k $ people.

## 说明/提示

In the first test case:

- $ k=1 $ : change the direction of $ 1 $ person to make the line RLR. The total value is $ 2+1+0=3 $ .
- $ k=2 $ : change the direction of $ 2 $ people to make the line RLL. The total value is $ 2+1+2=5 $ .
- $ k=3 $ : change the direction of $ 2 $ people to make the line RLL. The total value is $ 2+1+2=5 $ . Note that you have to change the direction of at most $ k $ people.

In the second test case, it is optimal to only change the direction of the first person for all $ k $ from $ 1 $ to $ 5 $ (that is, make the line RRRLL).

## 样例 #1

### 输入

```
6
3
LLR
5
LRRLL
1
L
12
LRRRLLLRLLRL
10
LLLLLRRRRR
9
LRLRLRLRL```

### 输出

```
3 5 5 
16 16 16 16 16 
0 
86 95 98 101 102 102 102 102 102 102 102 102 
29 38 45 52 57 62 65 68 69 70 
44 50 54 56 56 56 56 56 56```

# 题解

## 作者：ScottSuperb (赞：15)

# 解法分析
采取贪心策略，显然站在越靠近队伍两端的人改变其方向对结果的改变就越大，所以从 $0$ 到 $(\left \lfloor \frac{n}{2} \right \rfloor - 1)$ 枚举当前的人与队伍两端的距离 $dis$，再检查当前这个人是否需要改变方向（显然左边的人朝右更好，右边的人朝左更好），如果需要改变则将答案加上 $(n- dis- 1- dis)$，并将已改变方向的人数 $cnt$ 加 $1$ 再输出答案，保证 $cnt\le n$ 即可。当右边的人被检查后，因为左边一定已经检查过了，所以 $dis$ 自增。因为找到最大值后可更改次数再大答案都是一样的，全部检查完后将后面的输出即可。
# 代码
快读快输函数定义已省略。
```cpp
#include <bits/stdc++.h>

using namespace std;

#define ll long long

int main() {
	int t = read(), n, n2, dis, cnt;
	while (t--) {
		n = read();
		string s;
		ll ans = 0;
		for (int i = 0; i < n; ++i)
			s += getchar(), ans += s[i] == 'L' ? i : n - i - 1;
		for (cnt = dis = 0, n2 = n >> 1; dis < n2; ++dis) {
			if (s[dis] == 'L')
				ans += n - dis - 1 - dis, ++cnt, write(ans);
			if (s[n - dis - 1] == 'R')
				ans += n - dis - 1 - dis, ++cnt, write(ans);
		}
        while (n >= ++cnt)
            write(ans);
        putchar('\n');
	}
	return 0;
}
```

---

## 作者：lihanwen12 (赞：8)

题目大意：  
有 $n$ 个人排成一行，每个人都朝左或者朝右看并且在数这个方向上他们能看到几个人，定义这一行的权值为每个人看到的人数之和。现在给定每个人最初面朝方向并且允许你至多将其中 $k$ 个人的面朝方向改变，询问当 $k=1,2,3,\cdots,n$ 时，这一行的权值最大是多少。  

解题思路：  
人的位置从 $1$ 开始计数，对于第 $i$ 个人，面朝左可以看到 $i-1$ 个人，面朝右可以看到 $n-i$ 个人。如果一个人原来面朝左扭头之后这一行的权值变化量为 $(n-i)-(i-1)$，同理原来面朝右扭头之后这一行的权值变化量为 $(i-1)-(n-i)$。显然如果一个人扭头之后看到人数变少即权值变化量小于零还不如不消耗这一个修改次数改变他的朝向，遇到这种情况将这个人的权值变化量设为 $0$。提出贪心策略，优先修改权值变化量较大的人。以权值变化量为关键字从大到小排序，依次选取即可。  

代码：  
```cpp
#include<bits/stdc++.h>
using namespace std;
long long read(){
	long long x=0,sgn=1;char ch=getchar();
	while(ch<'0' || ch>'9'){if(ch=='-')sgn=-1;ch=getchar();}
	while(ch>='0' && ch<='9'){x=(x<<3)+(x<<1)+(ch&15);ch=getchar();}
	return x*sgn;
}
void write(long long n,bool p){
	if(n<0){putchar('-');n=-n;}
	if(n==0){if(p)putchar('0');return;}
	write(n/10,0);putchar(n%10+'0');
}
struct node{
	long long val,up;
}a[200010];
bool cmp(node x,node y){
	return x.up>y.up;
}
long long t,n,ans;
char ch[200010];
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>ch[i];
			if(ch[i]=='L'){
				a[i].val=i-1;
				a[i].up=max((long long)0,(n-i)-(i-1));
			}
			else{
				a[i].val=n-i;
				a[i].up=max((long long)0,i-1-(n-i));
			}
		}
		ans=0;
		for(int i=1;i<=n;i++)
			ans+=a[i].val;
		sort(a+1,a+n+1,cmp);
		for(int i=1;i<=n;i++){
			cout<<ans+a[i].up<<" ";
			ans+=a[i].up;
		}
		cout<<endl;
	} 
	return 0;
}

```

---

## 作者：RoyWu1207 (赞：1)

这道题其实很简单。

写题目时，考虑全部情况即可。

不断地枚举左端点右端点，如果当前进行修改可以得到更优值，那么更改左端点或右端点。

考虑两种情况。

1. 当前区间右端点修改后可得到更大值，但是左端点位置更优但不用修改，更新左端点；

1. 当前区间左端点修改后可得到更大值，但是右端点位置更优但不用修改，更新右端点。

将每次更新后的结果存在数组当中，若当前已经最优，将 $cnt$ 到 $n$ 的值全部设为最大值即可。

**AC Code：**

```cpp
#include <iostream>

using namespace std;

int main() {
	long long t; cin >> t;
	while (t--) {
		long long n; cin >> n;
		string a; cin >> a;
		long long ans = 0;
		for (long long i = 0; i < n; i++)
			ans += (a[i] == 'L' ? i : n - i - 1);
		long long l = 0, r = n - 1, cnt = 0;
		while (l <= r) {
			if (l <= n - r - 1) {
				if (a[l] == 'L')
					ans += n - l - 1 - l, l++, cout << ans << ' ', cnt++;
				else
					l++;
			} else {
				if (a[r] == 'R')
					ans += r - (n - r - 1), r--, cout << ans << ' ', cnt++;
				else
					r--;
			}
		} for (long long i = cnt + 1; i <= n; i++)
			cout << ans << ' ';
		cout << endl;
	} return 0;
}
```


---

## 作者：thh_loser (赞：1)

# CF1722D Line题解

## 题目描述

给你一个长度为 $n$，由 $L$ 和 $R$ 组成的字符串。如果为 $L$，这个字符的分数为左边字符的个数；如果为 $R$，这个字符的分数为右边字符的个数。这个字符串的总和为每个字符的分数之和。现给出一种操作一次能使一个 $L$ 变成 $R$，或者一个 $R$ 变成 $L$。问改变 $1 \sim n$ 次能得到的最大分数分别为多少。

## 思路

每个字符读入时先处理，更新初始分数，再判断改变该字符是否能增加分数，如果可以将增加的分数加入数组，否则就不能改变，加入 $0$。最后将数组里的数按降序排序，这样每次改变时就能增加最多的分数，得到的也就是最大的分数。

## code

```cpp

#include<bits/stdc++.h>
using namespace std;
int t,n,cs,maxx;
int sl[200010];
char c[200010];
long long ans;
int main(){
	scanf("%d",&t);
	while(t--){
		ans=0;
		scanf("%d",&n);
		for(int i=0;i<n;i++){
			cin>>c[i];
			if(c[i]=='L'){
				ans+=i;//更新分数 
				if(n-i-1>i){//如果能增加分数 
					sl[i]=n-i-1-i;
				}
				else{//否则加入0 
					sl[i]=0;
				}
			}
			else{
				ans+=(n-i-1);//更新分数 
				if(i>n-i-1){//如果能增加分数 
					sl[i]=i-n+i+1;
				}
				else{
					sl[i]=0;
				}
			}
		}
		sort(sl,sl+n);//排序 
		for(int i=n-1;i>=0;i--){//从高到低处理 
			ans+=(long long)sl[i];//更新分数 
			printf("%lld ",ans);
		}
		printf("\n");
		for(int i=0;i<n;i++){
			sl[i]=0;
		}//清零 
	}
	return 0;
}
```


---

## 作者：Epi4any (赞：1)

# 血的教训：不开 long long 见祖宗！

去世链接：[link](https://www.luogu.com.cn/discuss/487155)

很明显，这道题要求 $O(nt)$ 解决，也就是说答案我们有必要一次性算出答案，不能进行复杂的枚举。

所以我们大致思路是这样的：每个人转一下都能对答案做出一定的改变，然后我们贪心地选取贡献最大的先做出改变，贡献较小的在后面改变，还有，贡献是负的不做任何改变。

具体实现方法就是排序，然后一个一个的加，再输出。

注意：贡献值必定是正的，还有**一定一定一定要开 long long！**

代码：
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

#define int long long

int t, n;

bool cmp(int x, int y) {
	return x > y;
}

int max(int x, int y) {
	return x > y ? x : y;
}

signed main() {
	cin >> t;
	while (t--) {
		n = read();
		int ans = 0, p[200005];
		
		for (int i = 1; i <= n; i++) {
			char c;
			cin >> c;
			int l = i - 1, r = n - i;//l是头朝左可以看见的人数，r是头朝右可以看见的人数 
			if (c == 'L') ans += l, p[i] = max(r - l, 0);//头朝左 
			else ans += r, p[i] = max(l - r, 0);//头朝右 
		}
		
		sort(p + 1, p + n + 1, cmp);
		for (int i = 1; i <= n; i++) {
			cout << ans + p[i] << " ", ans += p[i];//加上然后输出
		}
		cout << endl;
	}
	return 0;
}
//结尾警告：理解思路，杜绝抄袭 
```


---

## 作者：二叉苹果树 (赞：0)

### 思路概述
本题的思路很简单，对于每个字符串，我们可以先预处理出每个字符经过变换后对答案的贡献，再将贡献值从大到小累加，如此保证每次变换后都是当前操作次数下的最大答案. 注意到，**可能会有字符在变换后对答案的贡献为负**，这个时候我们考虑不对这类字符进行变换操作，而是选择某些变化后对答案的贡献为 $0$ 的字符进行操作，例如每个字符串中的第一个和最后一个字符.

### 具体实现
记题目中所求得分为 $ans$. 对于每一个 $s[i]$ ，其左侧共有 $i$ 个字符，右侧共有 $(k-i-1)$ 个字符. 即 $s[i]$ 分别为 ```L``` 和 ```R``` 时，其对 $ans$ 的贡献值.

进一步地，将每一个 ```L``` 转化为 ```R``` 时，对 $ans$ 的贡献为 $(k-i-1)-i$；将每一个 ```R``` 转化为 ```L``` 时，对 $ans$ 的贡献为 $i-(k-i-1)$.

特殊地，当变化后贡献为负时，将贡献赋值为 $0$ .

### 温馨提示

本题输出数据量大，请使用较为快速地输出方式.

### 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;
bool cmp(int x,int y)
{
    return x>y;
}
int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        int k;
        string ss;
        char ch;
        cin>>k>>ch;
        getline(cin,ss);
        int v[100005];
        long long ans=0;
        string s=ch+ss;
        for(int i=0;i<k;i++)
        {
            if(s[i]=='L')
                v[i]=max((k-i-1)-i,0),ans+=i;
            else
                v[i]=max(i-(k-i-1),0),ans+=(k-i-1);
        }
        sort(v,v+k,cmp);
        for(int i=0;i<k;i++)
        {
            ans+=(long long)v[i];
            printf("%lld ",ans);
        }
        cout<<endl;
    }
    return 0;
}
```


---

## 作者：pokefunc (赞：0)

### 题意

直线上有 $n$ 个人，每个人最初可能向左看或向右看，对于 $i \in [1..n]$ 求在**至多**调整 $i$ 个人的朝向的情况下所有人能看到的人数的总和最大值。

### 题解

如果从左往右第 $i$ 个人向左看，那么可以看到 $i-1$ 个人；反之，可以看到 $n-i$ 个人。

因此，左半部分的人向右看是更优的，右半部分的人向左看是更优的，在有奇数个人的的情况下中间的人怎么站是无所谓的。

由于题目要求是**至多**，因此在所有人调整到最优状态了之后就不需要调整了。

又因为题目求的是前缀区间最大值，因此我们应当先调整那些获利最大的人。

于是我们可以把调整后可以获利的人按照获利的多少从高到低排序，然后求一个前缀和就能得到答案。

考虑到 $n=2 \times 10^5$，排序是可行的。

某和我一起打比赛的同学没看见“所有 $n$ 之和不大于 $2 \times 10^5$”这句话，居然搓出来一个 $O(n)$ 做法！

### 坑点

甚至出题人都提醒你开`long long`！

### 赛时代码

丑得离谱。

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#define int long long
using std::sort;
inline int read(){int x(0),op(0);char ch=getchar();while(ch<'0'||ch>'9')op|=(ch==45),ch=getchar();while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();return op?-x:x;}
char s[200005];
int re[200005],tt[200005];
signed main(){
	int t=read();
	while(t--){
		int n;
		memset(re,0,sizeof(re));
		scanf("%lld%s",&n,s+1);
		if(n==1){puts("0");continue;}
		int l1=1,r1,l2,r2=n;
		int ss=0;
		for(int i=1;i<=n;++i)ss+=tt[i]=(s[i]=='L'?i-1:n-i); //计算原方案能看到的人数总和
		if(n&1)r1=n/2,l2=n/2+2;
		else r1=n/2,l2=n/2+1;
		for(int i=l1;i<=r1;++i)re[i]=(s[i]=='L'?n-i-tt[i]:0);
		for(int i=l2;i<=r2;++i)re[i]=(s[i]=='R'?i-1-tt[i]:0);
		sort(re+1,re+n+1);
		for(int i=n;i;i--){
			printf("%lld ",ss+re[i]);
			ss+=re[i];
		}
		puts("");
	}
	return 0;
}
```



---

## 作者：hayzxjr (赞：0)

upd on 2023/10/20：修改码风及几处表述。

### 题意简述
给出由 $n$ 个人组成的一个左右排开队伍，每个人都有一个朝向，只能为 `L` 或 `R`，定义该排列的值为每个人面前的人数之和。

再给出一个正整数 $k$，对于所有 $i(i=1\sim k)$，求出分别将队伍中 **至少** $i$ 个人调转方向后所能得到的最大的队伍排列值。

### 题目分析

一个明显的贪心直觉，若某个人在队伍的前一半，那么一定要想后一半看；若在后一半则要向前一半看；若在中间（只有当 $n$ 为奇数时才有可能出现）则无所谓向哪看。这样便可将队伍分成 $\left[1,\left\lfloor\dfrac{n}{2}\right\rfloor\right]$ 和 $\left[\left\lfloor\dfrac{n}{2}\right\rfloor+1,n\right]$ 两个区间分别考虑。

贪心证明过于显然，不多赘述。

那么我们考虑 $f_i$ 表示若将第 $i$ 个翻转后的贡献，当然这个贡献可正可负。为下文解释方便，设 $d_i$ 为第 $i$ 个人的朝向，$1$ 则为朝右，$-1$ 为朝左。便能得到 $f_i$ 的计算方式：
$$
f_i = -d_i \times \left[(n - i)-(i-1)\right]
$$
其中 $-d_i$ 则为翻转方向，后面括号里的则为第 $i$ 个人右边的人减去左边的人的值。

然后把所有正的 $f_i$ 加到另一个数组 $p$ 中并排序，然后用一个指针 `now` 指向下一个要取的数，取 $k$ 次即可，注意，若 $p$ 中元素不足 $k$ 个，则说明不需要调 $k$ 个人的位置也能到达最优值，后面若要再取，可直接输出该最优值，毕竟题目有提到 **无需取满**。

下半部分的贪心，我们采取每步最优的方式能够达到局部最优 + 全局最优。这个证明思路也很明显，不再赘述。

### 代码实现

注意多测，~~避免不测~~。
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 200005
using namespace std;
int t, n, p[N];
string s;
bool cmp(int x, int y){return x > y;}
int main(){
	scanf("%d", &t);
	for(int z = 1; z <= t; z++){
		scanf("%d", &n);
		cin >> s;
		if(n == 1){
			printf("0\n");
			continue;
		}
		int tot = 0;
		ll ans = 0;
		for(int i = 1; i <= n; i++){ 
			if(s[i - 1] == 'L') ans = ans + i - 1;
			else ans = ans + n - i;
			if(i <= n / 2 && s[i - 1] == 'L') p[++tot] = n - 2 * i + 1;
			else if(i > n / 2 && s[i - 1] == 'R') p[++tot] = 2 * i - n - 1;
		}
		sort(p + 1, p + tot + 1, cmp);
		int now = 1;
		for(int k = 1; k <= n; k++){
			if(now <= tot){
				ans = ans + p[now];
				now++;
			}
			printf("%lld ", ans);
		}
		printf("\n");
	}
    return 0;
}
```

---

## 作者：Lantrol (赞：0)

### 题目描述

给定长度为 $n$ 的序列 $s$。

- $s_i$ 为 `L` 时，权值为在其左边的元素数量。

- $s_i$ 为 `R` 时，权值为在其右边的元素数量。

序列的权值为该序列中所有元素的权值和。有 $k$ 次修改机会，可将任意 $s_i$ 修改为与其相反的值，对于所有 $k\in[1,n]$，试求序列的最大权值。

### 思路

考虑贪心。显然，$s_i$ 为 `L` 时，其对答案的贡献为 $i-1$，为 `R` 时，对答案的贡献为 $n-i$ 。

不难证明：

- 当 $i< \dfrac{n+1}{2}$ 时，$n-i>i-1$，此时 $s_i$ 为 `R` 取到较大贡献。

- 当 $i> \dfrac{n+1}{2}$ 时，$i-1>n-i$，此时 $s_i$ 为 `L` 取到较大贡献。

再来考虑 $k$ 次修改的限制下，如何才能取到全局最优解。

- 当 $i< \dfrac{n+1}{2}$ 时，修改 $s_i$ 所增加的贡献为 $n-2i+1$，所以应该选最小的、值为 `L` 的 $s_i$ 进行修改。

- 当 $i> \dfrac{n+1}{2}$ 时，修改 $s_i$ 所增加的贡献为 $2i-n-1$，所以应该选最大的、值为 `R` 的 $s_i$ 进行修改。

那么，本题的做法也已经很明显了：

- 先扫一遍 $s$，求出修改前的初始总贡献。

- 枚举 $i\in[1,\dfrac{n+1}{2}]$，判断对于当前 $i$，是否有 $s_i$ 或 $s_{n-i+1}$ 可以被修改。

- 每次修改后更新总贡献。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

void solve(){
	int n;
	long long ans=0;
	string s;
	cin>>n>>s;
	for(int i=0;i<n;i++){
		if(s[i]=='L'){
			ans+=i;
		}
		if(s[i]=='R'){
			ans+=n-i-1;
		}
	}
	int i=0;
	for(int k=1;k<=n;k++){
		for(;i<n/2;i++){
			if(s[i]=='L'||s[n-i-1]=='R'){
				ans-=i;
				ans+=(n-i-1);
				if(s[i]=='L'){
					s[i]='R';
				}
				else{
					s[n-i-1]='L';
				}
				break;				
			}
		}
		cout<<ans<<" ";
	}
	cout<<endl;
}

int main(){
	int t;
	cin>>t;
	while(t--){
	    solve();
	}
}

```


---

## 作者：Kedit2007 (赞：0)

## 思路

对于每一个人，我们可以很容易地求出当前看到的人数和转身后看到的人数。那么我们只需要计算一下转身之后能多看见多少人。如果一个人转身后看见的人变少了，那么肯定不希望这个人转身，反之则需要转身。

用一个数组存储所有需要转身的人转身后能够多看到的人数，排序后直接从大的开始取即可。

## 参考代码

```cpp
vector<long long> Line(string line)
{
	long long sum = 0;
	vector<int> vec;
	
	int n = line.size();
	
	for (int i = 0; i < n; i++)
	{
		if (line[i] == 'L')
		{
			sum += i;
			// 转身后多看到的人数 
			int delta = (n - 1 - i) - i;
			if (delta > 0)
			{
				vec.push_back(delta);
			}
		}
		else
		{
			sum += n - 1 - i;
			// 转身后多看到的人数 
			int delta = i - (n - 1 - i);
			if (delta > 0)
			{
				vec.push_back(delta);
			}
		}
	}
	
	// sort后大的数在数组结尾 
	sort(vec.begin(), vec.end());
	
	vector<long long> ret(n);
	
	for (int i = 0; i < n; i++)
	{
		if (!vec.empty())
		{
			sum += vec.back();
			// vector 的 back() 和 pop_back() 时间复杂度都是 O(1) 
			vec.pop_back();
		}
		ret[i] = sum;
	}
	
	return ret;
}
```

---

## 作者：cyhtxdy (赞：0)

## 题意：
每个人都有一个看的方向，求一次最多改变 $k(1\le k \le n)$ 个人看的方向后，每个人能看到的人的总和的最大值。

## 思路：
首先将记录下不改变任何人的方向时的答案。

定义权值 $a_i$ 为改变第 $i$ 个人看的方向后，贡献的改变值。

那么将 $a_i$ 从大到小排，每次都累计 $a_i$ 并加上不改变时的答案。

由于最多改变 $k$ 个人的方向，那么当 $a_i$ 的贡献是负数时，我们就不需要将其积累到答案中。

## 代码：
```
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n, a[200005];
char c[200005];

int main () {
	int T;
	scanf ("%d", &T);
	while (T --) {
		scanf ("%d", &n);
		scanf ("%s", c + 1);
		int len = strlen (c + 1);
		ll ans = 0;
		for (int i = 1; i <= len; i ++) {
			if (c[i] == 'L') {
				a[i] = (n - i) - (i - 1);//计算权值
				ans += i - 1;//累计不改变时的答案
			}
			else {
				a[i] = (i - 1) - (n - i);//计算权值
				ans += n - i;//累计不改变时的答案
			}
		}
		sort (a + 1, a + 1 + n, greater<int>());//权值从大到小排序
		for (int i = 1; i <= n; i ++) {
			if (a[i] < 0) {
				printf ("%lld ", ans);//对答案无帮助时就不累计权值
			}
			else {
				printf ("%lld ", ans + a[i]);
				ans += a[i];
			}
		}
		puts ("");
	}
	
	return 0;
}
```


---

