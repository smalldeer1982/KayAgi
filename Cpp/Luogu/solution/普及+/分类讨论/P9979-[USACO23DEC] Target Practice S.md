# [USACO23DEC] Target Practice S

## 题目描述

Bessie 是一只仿生牛。在一条数轴上，她正尝试命中 $T$（$1 \leq T \leq 10^5$）个位于不同位置的靶子。Bessie 在位置 $0$ 开始行动，并遵循一个长度为 $C$（$1 \leq C \leq 10^5$）的命令序列，序列由 `L`、`F` 和 `R` 组成：

- `L`：Bessie 向左移动一个单位距离。
- `R`：Bessie 向右移动一个单位距离。
- `F`：Bessie 开枪。如果有一个靶子在 Bessies 当前的位置，这个靶子将被命中并摧毁。它不可以再次被命中。

如果在 Bessie 开始前，你被允许修改序列中的至多一条命令，Bessie 最多可以命中多少靶子？

## 说明/提示

### 样例解释 1

如果你对命令序列不做任何修改，Bessie 将命中两个靶子。

| 命令 | 位置 | 命中的靶子数目 |
| :----------- | :----------- | :----------- |
| Start | 0 | 0 |
| L | -1 | 0 |
| F | -1 | 1 |
| F | -1 | 1（无法摧毁靶子超过 1 次） |
| R | 0 | 1 |
| F | 0 | 2 |
| R | 1 | 2 |
| R | 2 | 2 |

如果你将最后一条命令由 `R` 修改为 `F`，Bessie 将命中三个靶子：

| 命令 | 位置 | 命中的靶子数目 |
| :----------- | :----------- | :----------- |
| Start | 0 | 0 |
| L | -1 | 0 |
| F | -1 | 1 |
| F | -1 | 1（无法摧毁靶子超过 1 次） |
| R | 0 | 1 |
| F | 0 | 2 |
| R | 1 | 2 |
| F | 1 | 3 |

### 样例解释 2

如果命令序列不修改，在位置 $0$ 的唯一一个靶子将被命中。

由于一个靶子不能被多次摧毁，答案为 $1$。

### 测试点性质

- 测试点 $4-6$ 满足 $T,C \le 1000$。
- 测试点 $7-15$ 没有额外限制。

## 样例 #1

### 输入

```
3 7
0 -1 1
LFFRFRR```

### 输出

```
3```

## 样例 #2

### 输入

```
1 5
0
FFFFF```

### 输出

```
1```

## 样例 #3

### 输入

```
5 6
1 2 3 4 5
FFRFRF```

### 输出

```
3```

# 题解

## 作者：Nuyoah_awa (赞：14)

### 题目大意

Bessie 在一个数轴上，这个数轴上有些点上有靶子，Bessie 需要按照指定命令行动，你可以修改一条命令，求出最多可以命中多少靶子。

### 题目分析

#### 思路

首先我们发现一共只能修改一条命令，我们观察对于修改后的命令哪些点会开火。

不难发现，对于修改前的命令，因为没有变，我们可以直接知道哪些点开火。对于修改后的命令，所有开火点的相对位置不会变，只会左右偏移 $1\sim2$ 个单位长度。

于是我们可以考虑枚举修改点，然后计算其答案（也可以看成枚举修改后的命令，因为总共只有 $C \times 3 + 1$ 种可能）。

思路有了，开始实现。

#### 实现及细节

我们先来想对于修改点前的点，我们只需要边枚举修改点，边存就行了，在这里我开了个 set。

然后考虑修改点后的点，我们可以预处理出偏移量为 $1\sim2$ 的开火点的集合，这里也可以开个 set。

然后问题就变成了如何计算两者之间重复的部分，我们发现我们可以将其都归在修改前算，即我们之前打过的点就不再打了，于是我们可以把打过的点在后面的 set 里删掉。

所以时间复杂度是 $\mathcal O(C \log C)$ 的。

然后算法就口糊出来了，开始实现。

第一个细节是维护后面的 set 时不仅要把之前打过的删掉，还要把“过期”的，也就是修改点之前的部分删掉。这个也很好实现，之前怎么加进来的就怎么删。

对于这个部分，由于 set 只有有和没有的区别，不好判断出了当前点，后面还有没有开火在这个位置，比较难处理，我在这里开了个筒子记个数，判断后面还有没有。

纯开 $5$ 个 set 然后删的话，你就会获得 $70 \sim 76 $ pts 的好成绩（也可能是我太菜了，第一遍好多细节都没注意到）。

第二个细节，对于将 `L` 或 `R` 改成 `F`，当前这个点需要计入答案，这个点能被计入有两个判断条件：
1. 当前位置有靶子。
2. 当前位置既没有在前面算过，后面也不会打到。

然后基本上代码就完善了。

最后还有一个小细节，就是可以不对命令进行修改，这种情况记得考虑到。

### code
```cpp
#include <iostream>
#include <cstdio>
#include <set>
#include <map>

using namespace std;

int T, c, x, ans;
string s;
map <int, bool> mp;
map <int, int> st[7];
set <int> se[7];

int main()
{
    scanf("%d %d", &T, &c);
    for(int i = 1;i <= T;i++)
    {
        scanf("%d", &x);
        mp[x] = true;
    }
    cin >> s;
    s = "#" + s;
    int now = 0;
    for(int i = 1;i <= c;i++)
    {
        if(s[i] == 'L')
        {
            now--;
        }
        else if(s[i] == 'R')
        {
            now++;
        }
        else
        {
            if(mp[now - 2]) st[1][now - 2]++, se[1].insert(now - 2);
            if(mp[now - 1]) st[2][now - 1]++, se[2].insert(now - 1);
            if(mp[now]) st[3][now]++, se[3].insert(now);
            if(mp[now + 1]) st[4][now + 1]++, se[4].insert(now + 1);
            if(mp[now + 2]) st[5][now + 2]++, se[5].insert(now + 2);
        }
    }
    ans = max(ans, (int)(se[3].size()));
    st[3].clear(), se[3].clear();
    now = 0;
//    printf("%d\n", ans);
    for(int i = 1;i <= c;i++)
    {
        if(s[i] == 'L')
        {
            ans = max(ans, (int)(se[3].size() + max(se[4].size() + (mp[now] && se[3].count(now) == 0 && se[4].count(now) == 0), se[5].size())));
            now--;
        }
        else if(s[i] == 'R')
        {
            ans = max(ans, (int)(se[3].size() + max(se[1].size(), se[2].size() + (mp[now] && se[3].count(now) == 0 && se[2].count(now) == 0))));
            now++;
        }
        else
        {
            se[1].erase(now);
            se[2].erase(now);
            se[4].erase(now);
            se[5].erase(now);
            if(--st[1][now-2] <= 0) se[1].erase(now-2);
            if(--st[2][now-1] <= 0) se[2].erase(now-1);
            if(--st[4][now+1] <= 0) se[4].erase(now+1);
            if(--st[5][now+2] <= 0) se[5].erase(now+2);
            ans = max(ans, (int)(se[3].size() + max(se[2].size(), se[4].size())));
            if(mp[now]) st[3][now]++, se[3].insert(now);
        }
//        printf("%d\n", ans);
    }
    printf("%d", ans);
    return 0;
}
```

### 附

附带一个小小小 hack：

in:
```
1 1
0
F
```
ans:
```
1
```
再附带一个[大样例](https://www.luogu.com.cn/paste/xoczo6s5)

### 写在后面

2024-1-17：感谢 @[whx1118](https://www.luogu.com.cn/user/928579) 的hack，已更正。

---

## 作者：naoliaok_lovely (赞：14)

大模拟题目，大致思路就是枚举把什么改成了什么。  
这里给出一份自认为容易理解的代码，方便后人参考。

tips：代码中用到了指针的技巧，作用就是让下标值域从 $[0,2N)$ 变为了 $[-N,N)$。

还是笼统的说几句吧：  
1. `l` 变为 `r`，相当于右移两位。
2. `l` 变为 `f`，相当于右移一位。
3. `r` 变为 `l`，相当于左移两位。
4. `r` 变为 `f`，相当于左移一位。
5. `f` 变为 `l`，相当于左移一位。
6. `f` 变为 `r`，相当于右移一位。

```
#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int n, m, X[2 * N], *x = X + N;
char c[N];
int Cnt[2 * N], *cnt = Cnt + N, pos, res, ans;

void get()
{
	pos = res = 0;
	memset(Cnt, 0, sizeof(Cnt));
	for(int i = 1; i <= m; i++)
		if(c[i] == 'L') pos--;
		else if(c[i] == 'R') pos++;
		else if(++cnt[pos] == 1 && x[pos]) res++;
	ans = max(res, ans);
}

void get_l_to_r()
{
	get();
	for(int i = m; i; i--)
		if(c[i] == 'L') pos++, ans = max(ans, res);
		else if(c[i] == 'R') pos--;
		else
		{
			if(!--cnt[pos] && x[pos]) res--;
			if(++cnt[pos + 2] == 1 && x[pos + 2]) res++;
		}
}

void get_l_to_f()
{
	get();
	for(int i = m; i; i--)
		if(c[i] == 'L') pos++, ans = max(ans, res + (!cnt[pos] && x[pos]));
		else if(c[i] == 'R') pos--;
		else
		{
			if(!--cnt[pos] && x[pos]) res--;
			if(++cnt[pos + 1] == 1 && x[pos + 1]) res++;
		}
}

void get_r_to_l()
{
	get();
	for(int i = m; i; i--)
		if(c[i] == 'L') pos++;
		else if(c[i] == 'R') pos--, ans = max(ans, res);
		else
		{
			if(!--cnt[pos] && x[pos]) res--;
			if(++cnt[pos - 2] == 1 && x[pos - 2]) res++;
		}
}

void get_r_to_f()
{
	get();
	for(int i = m; i; i--)
		if(c[i] == 'L') pos++;
		else if(c[i] == 'R') pos--, ans = max(ans, res + (!cnt[pos] && x[pos]));
		else
		{
			if(!--cnt[pos] && x[pos]) res--;
			if(++cnt[pos - 1] == 1 && x[pos - 1]) res++;
		}
}

void get_f_to_l()
{
	get();
	for(int i = m; i; i--)
		if(c[i] == 'L') pos++;
		else if(c[i] == 'R') pos--;
		else
		{
			if(!--cnt[pos] && x[pos]) res--;
			ans = max(ans, res);
			if(++cnt[pos - 1] == 1 && x[pos - 1]) res++;
		}
}

void get_f_to_r()
{
	get();
	for(int i = m; i; i--)
		if(c[i] == 'L') pos++;
		else if(c[i] == 'R') pos--;
		else
		{
			if(!--cnt[pos] && x[pos]) res--;
			ans = max(ans, res);
			if(++cnt[pos + 1] == 1 && x[pos + 1]) res++;
		}
}

int main()
{
	cin >> n >> m;
	for(int i = 1, a; i <= n; i++) scanf("%d", &a), x[a] = 1;
	scanf("%s", c + 1);
	
	get();
	get_l_to_r();
	get_l_to_f();
	get_r_to_l();
	get_r_to_f();
	get_f_to_l();
	get_f_to_r();
	
	cout << ans << endl;
	return 0;
}
```

---

## 作者：Loser_Syx (赞：6)

发现改变字符只会有六种：`L->R`、`L->F`、`R->L`、`R->F`、`F->L`、`F->R`，对应偏移量依次为 $\{+2,+1,-2,-1,-1,+1\}$。

于是就可以直接枚举是在哪个点上改变的，具体而言，先预处理出 $6$ 种情况不进行改变时的答案，然后倒序枚举变的点，按当前字母与 $6$ 种情况依次进行即可：

- 当前字符为 `L`，对更改此字符至 `R` 和 `F` 的情况取 $\max$ 即可。

- 当前字符为 `R`，对更改此字符至 `L` 和 `F` 的情况取 $\max$ 即可。

- 当前字符为 `F`，需要对于每个偏移量计算出每种情况这一发打在哪里并清除之前的历史。之后对更改至 `L` 和 `R` 的情况取 $\max$ 即可。

答案显然是 $\max$ 值。

```cpp
int e[6][200010], cnt[6];
/*
e[0]: L->R
e[1]: L->F
e[2]: R->L
e[3]: R->F
e[4]: F->L
e[5]: F->R
*/
int place[200010];
bitset<200010> bt;
signed main() {
	int n = read(), m = read();
	for (int i = 1; i <= n; ++i) {
		bt[read() + 100000] = 1;
	}
	string s;
	cin >> s;
	for (int i = 0, x = 0; i < m; ++i) {
		if (s[i] == 'L') x--;
		else if (s[i] == 'R') x++;
		else {
			if (bt[x + 100000] == 1) {
				if (e[0][x + 100000] == 0) {
					cnt[0] = cnt[1] = cnt[2] = cnt[3] = cnt[4] = ++cnt[5];
				}
				e[0][x + 100000] ++;
				e[1][x + 100000] ++;
				e[2][x + 100000] ++;
				e[3][x + 100000] ++;
				e[4][x + 100000] ++;
				e[5][x + 100000] ++;
			}
		}
		place[i] = x;
	}
	int ans = cnt[0];
	for (int i = m - 1; ~i; --i) {
		if (s[i] == 'L') {
			int now = place[i] + 1;
			if (bt[now + 100000] == 1) {
				if (e[1][now + 100000]++ == 0) cnt[1] ++;
				ans = max(ans, cnt[1]);
				if (--e[1][now + 100000] == 0) cnt[1] --;
			}
			ans = max(ans, cnt[0]);
		}
		if (s[i] == 'R') {
			int now = place[i] - 1;
			if (bt[now + 100000] == 1) {
				if (e[3][now + 100000]++ == 0) cnt[3] ++;
				ans = max(ans, cnt[3]);
				if (--e[3][now + 100000] == 0) cnt[3] --;
			}
			ans = max(ans, cnt[2]);
		}
		if (s[i] == 'F') {
			int now = place[i];
			if (bt[now + 100000] == 1) { // 清除历史 
				if (--e[0][now + 100000] == 0) cnt[0] --;
				if (--e[1][now + 100000] == 0) cnt[1] --;
				if (--e[2][now + 100000] == 0) cnt[2] --;
				if (--e[3][now + 100000] == 0) cnt[3] --;
				if (--e[4][now + 100000] == 0) cnt[4] --;
				if (--e[5][now + 100000] == 0) cnt[5] --; 
			}
			if (bt[now + 100000 + 2] == 1) { // L -> R 的 F 
				if (e[0][now + 100000 + 2]++ == 0) cnt[0] ++;
			}
			if (bt[now + 100000 + 1] == 1) { // L -> F
				if (e[1][now + 100000 + 1]++ == 0) cnt[1] ++;
			}
			if (bt[now + 100000 - 2] == 1) { // R -> L
				if (e[2][now + 100000 - 2]++ == 0) cnt[2] ++;
			}
			if (bt[now + 100000 - 1] == 1) {
				if (e[3][now + 100000 - 1]++ == 0) cnt[3] ++;
			}
			ans = max(ans, cnt[4]); // F -> L
			if (bt[now + 100000 - 1] == 1) {
				if (e[4][now + 100000 - 1]++ == 0) cnt[4] ++;
			}
			ans = max(ans, cnt[5]); // F -> R
			if (bt[now + 100000 + 1] == 1) {
				if (e[5][now + 100000 + 1]++ == 0) cnt[5] ++;
			}
		}
	}
	write(ans, '\n');
	return 0;
}
```

---

## 作者：听取MLE声一片 (赞：5)

修改把操作分成两部分，即操作前和操作后。

而修改操作至多让以后的操作移动两位，所以只需要考虑不变、左移一位、左移两位、右移一位、右移两位即可。

首先处理出每一步的位置。前半部分是简单的，后半部分是复杂的。而拓展是简于删除的，所以合理的方案是从后到前枚举修改点，后半部分加点，前半部分删点。初始时前半部分都是满的，不断的删点；初始时后半部分都是空的，不断的加点。

靶子是不可以再次被命中的，所以要记录哪些靶子已经被命中过了。

具体的，记录每个靶子被打击的次数。若次数降为 $0$ 则这个地方的贡献被撤销，答案要减一。若对应位置在后半部分由被命中过则不需要减。后半部分命中前半部分没有命中的靶子（后半部分内部也没命中过）时答案要加一。

剩下就是五种状态的讨论了，稍微想想就可以了。

由此得到了一个线性做法。


```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
#include<map>
#include<set>
#include<bitset>
#include<ctime>
#include<random>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=1e5+10;
int n,m,a[N],f[5],vis[5][N],ans,res,cnt;
char str[N];
map<int,int>mp,sum;
int main()
{
	m=read(),n=read();
	for(int i=1;i<=m;i++){
		int x=read();
		mp[x]=i;
	}
	scanf("%s",str+1);
	for(int i=1;i<=n;i++){
		a[i]=a[i-1];
		if(str[i]=='L')a[i]--;
		if(str[i]=='R')a[i]++;
		if(str[i]=='F'){
			int u=mp[a[i]];
			if(u){
				if(sum[u]==0)res++;
				sum[u]++;
			}
		}
	}
	ans=res;
	for(int i=n;i>=1;i--){
		if(str[i]=='F'){
			int u=mp[a[i]];
			if(u){
				sum[u]--;
				if(sum[u]==0){
					res--;
					for(int j=0;j<5;j++){
						if(vis[j][u])
							f[j]++;
					}
				}
			}
		}
		if(str[i]=='L'){
			int x=0;
			int u=mp[a[i]+1];
			if(u&&sum[u]==0&&!vis[3][u])x=1;
			ans=max(ans,res+f[3]+x);
			ans=max(ans,res+f[4]);
		}
		if(str[i]=='R'){
			int x=0;
			int u=mp[a[i]-1];
			if(u&&sum[u]==0&&!vis[1][u])x=1;
			ans=max(ans,res+f[1]+x);
			ans=max(ans,res+f[0]);
		}
		if(str[i]=='F'){
			ans=max(ans,res+f[3]);
			ans=max(ans,res+f[1]);
		}
		if(str[i]=='F'){
			for(int j=0;j<5;j++){
				int u=mp[a[i]+(j-2)];
				if(u){
					if(!vis[j][u]){
						vis[j][u]=1;
						if(!sum[u])f[j]++;
					}
				}
			}		
		}
	}
	cout<<ans;
	return 0;
}

```



---

## 作者：Night_sea_64 (赞：3)

首先这道题我们发现：如果改掉一条命令，那么这条及以后的命令，牛的位置会偏移 $1,2,-1$ 或 $-2$。

可以把每个 `F` 操作都加到它对应的位置里。在枚举每个位置尝试修改的时候，我们需要快速地知道修改完以后的新答案。设枚举到第 $i$ 条命令，我们需要知道的就是第 $1\sim i-1$ 条命令牛的位置不变，第 $i$ 条及以后的命令牛的位置变化的答案。答案是存在 `F` 操作的位置的个数。

为此，我们只需要预先处理出牛的初始位置为 $1,2,-1,-2$ 时答案是多少，这时每个 `F` 操作的位置也加上了这个偏移量。扫描到每一条命令时，先尝试修改，然后如果这条命令是 `F`，那么在四种情况中都把这条 `F` 的位置复原（即取消它的偏移量），就可以保证后面尝试修改时，前面的 `F` 都复原了。

细节问题见代码。

```cpp
#include<iostream>
using namespace std;
int n,m,now,ans,k;
bool flag[300010];
int t[100010],id[300010]; 
int cnt[5][300010],sum[5];
char a[100010];
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        cin>>t[i];
        t[i]+=200000;
        id[t[i]]=i;
    }
    now=200000;
    for(int i=1;i<=m;i++)
    {
        cin>>a[i];
        if(a[i]=='L')now--;
        if(a[i]=='R')now++;
        if(a[i]=='F'&&id[now]&&!flag[now])k++,flag[now]=1;
    }
    for(int k=-2;k<=2;k++)
    {
        if(!k)continue;
        now=k+200000;
        for(int i=1;i<=m;i++)
        {
            if(a[i]=='L')now--;
            if(a[i]=='R')now++;
            if(a[i]=='F')
            {
                if(id[now])
                    cnt[k+2][now]++,sum[k+2]+=(cnt[k+2][now]==1);
            }
        }
    }
    now=200000;
    for(int i=1;i<=m;i++)
    {
        if(a[i]=='L')
        {
            ans=max(ans,sum[4]);
            ans=max(ans,sum[3]+(id[now]>0&&!cnt[3][now]));
        }
        if(a[i]=='R')
        {
            ans=max(ans,sum[0]);
            ans=max(ans,sum[1]+(id[now]>0&&!cnt[1][now]));
        }
        if(a[i]=='F')
        {
            ans=max(ans,sum[1]-(id[now]>0&&cnt[1][now]==1));
            ans=max(ans,sum[3]-(id[now]>0&&cnt[2][now]==1));
        }
        if(a[i]=='L')now--;
        if(a[i]=='R')now++;
        if(a[i]=='F')
        {
            for(int j=-2;j<=2;j++)
            {
                if(!j)continue;
                if(id[now])cnt[j+2][now]++,sum[j+2]+=(cnt[j+2][now]==1);
                if(id[now+j])cnt[j+2][now+j]--,sum[j+2]-=(!cnt[j+2][now+j]);
            }
        }
    }
    cout<<max(ans,k)<<endl;
    return 0;
}
```

---

## 作者：0000pnc (赞：3)

题意：数轴上有 $t$ 个目标（位置两两不同），你现在在 $0$ 处。给定长度为 $c$ 的命令串（包含 `L`，`R`，`F` 三种字母），你需要按照命令串依次执行命令：`L` 表示向左走一步，`R` 表示向右走一步，`F` 表示在当前位置开火，如果该位置有未被击中过的目标则其被击中。你有一次修改的机会（可以不用），使命令串的一个字符改变。问最多能击中多少个目标。

注意到一次修改之后，操作位置后面的整个串的行为发生的位置都会偏移相同的长度。（比如：`RRLFFRF` 将 `L` 改成 `R` 后，后面的每一次操作发生的位置都会 $+2$。）那么我们可以先预处理出没有修改时的每个动作的位置在哪里。对于每个位置，记录它被打了多少次，以及记录初始时的答案。

然后我们可以枚举偏移的长度（$-1$，$1$，$-2$，$2$ 四种），然后在命令串中从右往左进行扫描线。涉及的操作有：撤销一次开火、进行一次开火，询问当前有多少个目标被击中。直接维护即可。具体的细节可以看代码。

时间复杂度 $\mathcal{O}(c)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
int max(int x, int y) { return (x > y ? x : y); }

int T, c, buc[200015], cnt, pos[100015];
bool vis[200015];
char s[100015];

void init() {
	memset(buc, 0, sizeof buc);
	int now = c + 10; cnt = 0;
	for (int i = 1; i <= c; i++) {
		if (s[i] == 'L') now--;
		if (s[i] == 'R') now++;
		if (s[i] == 'F') {
			if (vis[now]) {
				if (!buc[now]) cnt++;
				buc[now]++;
			}
		}
		pos[i] = now;
	}
}

int work1() { // 0
	init(); return cnt;
}

int work2() { // 2
	init(); int ans = 0;
	for (int i = c; i; i--) {
		if (s[i] == 'F') {
			buc[pos[i]]--;
			if (!buc[pos[i]]) cnt--;
			if (vis[pos[i] + 2]) {
				if (!buc[pos[i] + 2]) cnt++;
				buc[pos[i] + 2]++;
			}
		}
		if (s[i] == 'L') ans = max(ans, cnt);
	}
	return ans;
}

int work3() { // -2
	init(); int ans = 0;
	for (int i = c; i; i--) {
		if (s[i] == 'F') {
			buc[pos[i]]--;
			if (!buc[pos[i]]) cnt--;
			if (vis[pos[i] - 2]) {
				if (!buc[pos[i] - 2]) cnt++;
				buc[pos[i] - 2]++;
			}
		}
		if (s[i] == 'R') ans = max(ans, cnt);
	}
	return ans;
}

int work4() { // 1
	init(); int ans = 0;
	for (int i = c; i; i--) {
		if (s[i] == 'L') {
			if (vis[pos[i] + 1]) {
				if (!buc[pos[i] + 1]) cnt++;
				buc[pos[i] + 1]++;
			}
			ans = max(ans, cnt);
			if (vis[pos[i] + 1]) {
				buc[pos[i] + 1]--;
				if (!buc[pos[i] + 1]) cnt--;
			}
		}
		if (s[i] == 'F') {
			buc[pos[i]]--;
			if (!buc[pos[i]]) cnt--;
			ans = max(ans, cnt);
			if (vis[pos[i] + 1]) {
				if (!buc[pos[i] + 1]) cnt++;
				buc[pos[i] + 1]++;
			}
		}
	}
	return ans;
}

int work5() { // -1
	init(); int ans = 0;
	for (int i = c; i; i--) {
		if (s[i] == 'R') {
			if (vis[pos[i] - 1]) {
				if (!buc[pos[i] - 1]) cnt++;
				buc[pos[i] - 1]++;
			}
			ans = max(ans, cnt);
			if (vis[pos[i] - 1]) {
				buc[pos[i] - 1]--;
				if (!buc[pos[i] - 1]) cnt--;
			}
		}
		if (s[i] == 'F') {
			buc[pos[i]]--;
			if (!buc[pos[i]]) cnt--;
			ans = max(ans, cnt);
			if (vis[pos[i] - 1]) {
				if (!buc[pos[i] - 1]) cnt++;
				buc[pos[i] - 1]++;
			}
		}
	}
	return ans;
}

int main() {
	scanf("%d %d", &T, &c);
	for (int i = 1, x; i <= T; i++) {
		scanf("%d", &x); vis[x + c + 10] = 1;
	}
	scanf("%s", s + 1);
//	printf("%d %d %d %d %d\n", work1(), work2(), work3(), work4(), work5());
	printf("%d\n", max({work1(), work2(), work3(), work4(), work5()}));
}
```

---

## 作者：寒鸽儿 (赞：2)

提供一种比较好写的思路：

基本思想是枚举每个位置，当前的字母枚举变成了什么字母。

对于同一种变化，那么某个位置变化后，其后面的攻击 `F` 发生时所在的位置的变化量是确定的。

预处理出不发生变化时每次操作操作前所处的位置。

对每种变化分别枚举所有位置。从后往前枚举，当前枚举的点之后的点都是变化后的位置。如果这个字母符合变化，则将当前的答案更新全局最优解。然后修改当前操作的位置（维护下面的枚举）：统计全局每个 target 第一个被击中的 `F` 发生的下标，在移动到某个位置的时候，如果原有位置是 `F` ，那么需要判断是不是 left，如果是，用后面的最近的相同位置的 `F`（如果存在）更新 target，不存在则 left 置为 $0$ 。同时更新变到的位置的 left（如果可以）。使用一个变量全局地记录 left 中非 $0$ 的 target 点的个数，即为当前枚举的答案。（也可以写成 cnt 数组，更好写一点）。

复杂度 $\mathcal{O}(n)$ 。

```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)

using namespace std;

const int N = 1e5 + 10, DELTA = 1e5 + 1;
int pls[N], mp[N << 1], lft[N << 1], second[N << 1], LEFT[N << 1], nTar, nOp, curAns, ans;
char op[N];

void work(int delta, char from, char to) {
    memset(second, 0, sizeof(second));
    memcpy(lft, LEFT, sizeof(lft));
    per(i,nOp,1) {
        if(op[i] == from) {
            if(from == 'F' && mp[pls[i] + DELTA] && lft[pls[i] + DELTA] == i && second[pls[i] + DELTA] == 0) ans = max(ans, curAns - 1);
            else if(to == 'F' && mp[pls[i] + DELTA] && lft[pls[i] + DELTA] == 0) ans = max(ans, curAns + 1);
            else ans = max(ans, curAns);
        }
        if(op[i] == 'F') {
            if(mp[pls[i] + DELTA] && lft[pls[i] + DELTA] == i) {
                lft[pls[i] + DELTA] = second[pls[i] + DELTA];
                if(lft[pls[i] + DELTA] == 0) -- curAns;
            }
            pls[i] += delta;
            if(mp[pls[i] + DELTA]) {
                if(lft[pls[i] + DELTA] == 0) ++ curAns, lft[pls[i] + DELTA] = i;
                second[pls[i] + DELTA] = i;
                lft[pls[i] + DELTA] = min(lft[pls[i] + DELTA], i);
            }
            pls[i] -= delta;
        }

    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> nTar >> nOp;
    int tar;
    rep(i,1,nTar) {
        cin >> tar;
        mp[tar + DELTA] = 1;
    }
    cin >> (op + 1);
    int x = 0;
    rep(i,1,nOp) {
        pls[i] = x;
        if(op[i] == 'L') -- x;
        else if(op[i] == 'R') ++ x;
        else if(mp[x + DELTA] && !lft[x + DELTA]) {
            ++ ans;
            lft[x + DELTA] = i;
        }
    }
    int tmp = ans;
    memcpy(LEFT, lft, sizeof(lft));
    curAns = tmp; work(2, 'L', 'R');
    curAns = tmp; work(-2, 'R', 'L');
    curAns = tmp; work(1, 'L', 'F');
    curAns = tmp; work(-1, 'R', 'F');
    curAns = tmp; work(-1, 'F', 'L');
    curAns = tmp; work(1, 'F', 'R');
    cout << ans << endl;
    return 0;
}
```



---

## 作者：strcmp (赞：2)

usaco 什么垃圾评测机啊，bitset 赛时 T，洛谷上没到 500ms。

------------

要会这题，你首先要会这题的 bitset 做法。

我们算出将所有操作都严格进行了之后的会射击的位置的状态 $a$，和靶子的状态 $b$。

然后倒序处理，维护后缀 bitset 的左移一二位，右移一二位的状态即可。

时间复杂度 $\Theta(\dfrac{n^2}{w})$，赛时喜提暴力分。

然后你发现因为我们后缀只用到了这四个状态，每次都暴力或与上去是非常亏的。

每个后缀状态单独的贡献是可以直接 $\Theta(1)$ 算的，于是就做完了。

时间复杂度 $\Theta(n)$，代码很屎。

```cpp
#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
typedef long long int ll;
using pll = pair<ll, ll>;
const int maxn = 2e5 + 10;
const ll mod = 998244353LL;
const ll inf = 1145141919810LL;
bitset<maxn>b1, b2, b3, b2y2, b2y1, b2z1, b2z2;
int t, c; int a[maxn], b[maxn], d[maxn]; char s[maxn];
int main() {
	ll y1 = 0, y2 = 0, z1 = 0, z2 = 0;
	scanf("%d%d", &t, &c); int now = 100002, tot = 0, mx = 0;
	for (int i = 1; i <= t; i++) scanf("%d", &a[i]);
	scanf("%s", s + 1);
	for (int i = 1; i <= c; i++) {
		b[i] = now;
		if (s[i] == 'L') --now;
		if (s[i] == 'R') ++now;
		if (s[i] == 'F') ++d[now], b1[now] = 1;
		//d[k] 1..i 位置 k 被标记了几次 
	}
	for (int i = 1; i <= t; i++) a[i] += 100002, b3[a[i]] = 1; // b3 目标
	ll ans = y1 = y2 = z1 = z2 = (b1 & b3).count();
	for (int i = c; i >= 1; i--) {
		//cout << y1 << " " << y2 << " " << z1 << " " << z2 << "\n";
		now = b[i];
		if (s[i] == 'L') {
			//now 不变，整个区间向右移
			ans = max(ans, y2); ll kal = 0;
			if (!d[now] && !b2y1[now] && b3[now]) ++y1, kal = 1;
			ans = max(ans, y1);
			y1 -= kal;
		}
		else if (s[i] == 'R') {
			ans = max(ans, z2); ll kal = 0;
			if (!d[now] && !b2z1[now] && b3[now]) ++z1, kal = 1;
			//ans = max(ans, (ll)((b1 | (b2z1)) & b3).count());
			ans = max(ans, z1);
			z1 -= kal;
		}
		else {
			int u = b1[now]; ll kal = 0;
			if (d[now] == 1 && !b2y1[now] && b3[now]) kal = 1, --y1;
			ans = max(ans, y1); y1 += kal; kal = 0;
			if (d[now] == 1 && !b2z1[now] && b3[now]) kal = 1, --z1;
			ans = max(ans, z1); z1 += kal; kal = 0;
		}
		if (s[i] == 'F') {
			int u = d[now]; --d[now];
			if (now + 2 < maxn) {
				int v = b2y2[now + 2];
				b2y2[now + 2] = 1;
				if (!b2y2[now] && b3[now] && u == 1) --y2;
				if (!d[now + 2] && b3[now + 2] && !v) ++y2;
			}
			if (now + 1 < maxn) {
				int v = b2y1[now + 1];
				b2y1[now + 1] = 1;
				if (!b2y1[now] && b3[now] && u == 1) --y1;
				if (!d[now + 1] && b3[now + 1] && !v) ++y1;
			}
			if (now - 1 >= 0) {
				int v = b2z1[now - 1];
				b2z1[now - 1] = 1;
				if (!b2z1[now] && b3[now] && u == 1) --z1;
				if (!d[now - 1] && b3[now - 1] && !v) ++z1;
			}
			if (now - 2 >= 0) {
				int v = b2z2[now - 2];
				b2z2[now - 2] = 1;
				if (!b2z2[now] && b3[now] && u == 1) --z2;
				if (!d[now - 2] && b3[now - 2] && !v) ++z2;
			}
		}
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：Zi_Gao (赞：1)

> 题意：
>
> 给一个数轴，上面有 $n$ 个目标分别在 $pos_i$ 的位置，然后有一个人首先站在原点，会依次执行 $m$ 个操作，每个操作可能是
>
> 1. 向左移动 $1$ 单位。
> 2. 向右移动 $1$ 单位。
> 3. 开火，若这个地方有目标，则目标被摧毁，不能摧毁已经摧毁的目标
>
> 但是现在要求把其中一个操作换成另一个不同的操作，问最多可以摧毁多少个目标。
>
> $n\leq 10^5,-m\leq pos_i\leq m$ 并且 $pos_i$ 互不相同

不妨先考虑去除一段前缀或者后缀操作最多摧毁多少个目标，显然可以维护一个桶 $buc_i$ 表示在 $buc_i$ 这个位置经过了多少次，若当前是第一次经过这个位置然后开火了，并且这里有个目标则会多摧毁一个目标。考虑枚举哪个位置的操作被修改，然后可以把问题转化为把前后两端操作的贡献合并起来，然后单独考虑这个位置的贡献，实际上可以使用 `bitset` 可以在 $\mathcal{O}\left(\frac{n}{w}\right)$ 的时间复杂的内对两个 `bitset` 求按位与、或、异或操作，以及对一个 `bitset` 求多少个位置值为 $1$。可以从后往前考虑，对于前缀每次减少一个操作出去并维护前缀经过位置的桶，以及可以打中的目标的 `bitset`，然后对于后缀，由于修改操作可能导致后缀位置发生集体偏移但是偏移绝对值不会超过 $2$ 维护同样一个桶和 $5$ 个 `bitset` 表示不同偏移量可以打中的目标，然后把前后缀对应两个桶求按位于，然后求多少个位置值为 $1$ 即可算出当前答案，时间复杂度 $\mathcal{O}\left(\frac{n^2}{w}\right)$。

这样做题有点对不起题目的意思，只是出题人不小心放过了这个算法。那就给出一个线性做法，还是仿照前面的过程，只不过动态维护前缀桶和 `bitset` 与每一个后缀 `bitset` 的并，以及每个 `bitset` 的并的答案，可以发现每次最多使桶内和每个 `bitset` 内一个值发生变化，只把这个变化领出来即可，那么答案变化也可以维护。

你说得对，但是我写的 $bitset$。

```cpp
#include<bits/stdc++.h>
#define ONLINE_JUDGE
#define INPUT_DATA_TYPE int
#define OUTPUT_DATA_TYPE int
INPUT_DATA_TYPE read(){register INPUT_DATA_TYPE x=0;register char f=0,c=getchar();while(c<'0'||'9'<c)f=(c=='-'),c=getchar();while('0'<=c&&c<='9')x=(x<<3)+(x<<1)+(c&15),c=getchar();return f?-x:x;}void print(OUTPUT_DATA_TYPE x){if(x<0)x=-x,putchar('-');if(x>9)print(x/10);putchar(x%10^48);return;}

char opers[500010];
int pos[500010],buc[500010],tar[500010];

std::bitset<100010> pre,suf[5],tmp;

int main(){
    #ifndef ONLINE_JUDGE
    freopen("name.in", "r", stdin);
    freopen("name.out", "w", stdout);
    #endif

    register int i,j,B,ans;
    int T=read();
    int C=read();
    B=140000;

    for(i=1;i<=T;++i) tar[read()+B]=i;
    scanf("%s",opers+1);

    for(i=1,pos[0]=B;i<=C;++i)
        if(opers[i]=='L') pos[i]=pos[i-1]-1;
        else if(opers[i]=='R') pos[i]=pos[i-1]+1;
        else{
            ++buc[pos[i]=pos[i-1]];
            if(tar[pos[i]]) pre[tar[pos[i]]]=1;
        }

    ans=pre.count();

    for(i=C;i;--i){
        if(i>1&&opers[i]=='F'){
            --buc[pos[i]];
            if(buc[pos[i]]==0&&tar[pos[i]]!=0) pre[tar[pos[i]]]=0;
        }
        if(opers[i]=='L'){
            ans=std::max(ans,(int)((suf[4]|pre).count()));

            tmp=(suf[3]|pre);
            if(tar[pos[i-1]]!=0) tmp[tar[pos[i-1]]]=1;
            ans=std::max(ans,(int)(tmp.count()));
        }else if(opers[i]=='R'){
            ans=std::max(ans,(int)((suf[0]|pre).count()));

            tmp=(suf[1]|pre);
            if(tar[pos[i-1]]!=0) tmp[tar[pos[i-1]]]=1;
            ans=std::max(ans,(int)(tmp.count()));
        }else ans=std::max({ans,(int)((suf[1]|pre).count()),(int)((suf[3]|pre).count())});
        if(opers[i]=='F')
            for(j=-2;j<=2;j++)
                if(tar[pos[i]+j]!=0) suf[j+2][tar[pos[i]+j]]=1;
    }

    print(ans);

    #ifndef ONLINE_JUDGE
    fclose(stdin);
    fclose(stdout);
    #endif
    return 0;
}
```


---

## 作者：mRXxy0o0 (赞：1)

# 分析

考虑不修改命令最终的代价，显然，这是可以扫一遍求出来的。

此时再来想怎么加入改动。

假设改动的是 `L` 。

- 改成了 `R`，那么后续所有开火点都会向右移 $2$。

- 改成了 `F`，那么当前加贡献，后续开火点都会向右移 $1$。

改 `R` 或 `F` 同理。

这启示我们处理出后缀开火点移动 $\pm1,2$ 的贡献。然后对于每一个位置，讨论改不改的贡献即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=3e5+10;
const ll inf=1e18;
int n,m,a[N],pos[N],l1[N],l2[N],r1[N],r2[N],s[N],ans,fg[N],us[5][N];
bool hav[5][N];
char op[N];
int main(){
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;++i){
		scanf("%d",&a[i]);
		a[i]+=n+5;
		fg[a[i]]=1;
	}
	scanf("%s",op+1);
	pos[0]=n+5;
	for(int i=1;i<=n;++i){
		s[i]=s[i-1];
		if(op[i]=='L') pos[i]=pos[i-1]-1;
		else if(op[i]=='R') pos[i]=pos[i-1]+1;
		else{
			pos[i]=pos[i-1];
			if(fg[pos[i]]){
				s[i]+=(us[0][pos[i]]==0);
				++us[0][pos[i]];
			}
		}
	}
	ans=s[n];
	for(int i=n;i;--i){
		l1[i]=l1[i+1],l2[i]=l2[i+1],r1[i]=r1[i+1],r2[i]=r2[i+1];
		if(op[i]=='F'){
			if(fg[pos[i]]){
				--us[0][pos[i]];
				if(!us[0][pos[i]]){
					l1[i]+=(hav[1][pos[i]]);
					l2[i]+=(hav[2][pos[i]]);
					r1[i]+=(hav[3][pos[i]]);
					r2[i]+=(hav[4][pos[i]]);
					hav[1][pos[i]]=hav[2][pos[i]]=hav[3][pos[i]]=hav[4][pos[i]]=0;
				}
			}
			if(fg[pos[i]-1]){
				l1[i]+=(us[0][pos[i]-1]==0&&us[1][pos[i]-1]==0);
//				cout<<i<<" "<<pos[i]-1<<" "<<us[0][pos[i]-1]<<" "<<us[1][pos[i]-1]<<"\n";
				if(us[0][pos[i]-1]&&!us[1][pos[i]-1]) hav[1][pos[i]-1]=1;
				++us[1][pos[i]-1];
			}
			if(fg[pos[i]-2]){
				l2[i]+=(us[0][pos[i]-2]==0&&us[2][pos[i]-2]==0);
				if(us[0][pos[i]-2]&&!us[2][pos[i]-2]) hav[2][pos[i]-2]=1;
				++us[2][pos[i]-2];
			}
			if(fg[pos[i]+1]){
				r1[i]+=(us[0][pos[i]+1]==0&&us[3][pos[i]+1]==0);
				if(us[0][pos[i]+1]&&!us[3][pos[i]+1]) hav[3][pos[i]+1]=1;
				++us[3][pos[i]+1];
			}
			if(fg[pos[i]+2]){
				r2[i]+=(us[0][pos[i]+2]==0&&us[4][pos[i]+2]==0);
				if(us[0][pos[i]+2]&&!us[4][pos[i]+2]) hav[4][pos[i]+2]=1;
				++us[4][pos[i]+2];
			}
		}
		if(op[i]=='L'){
			ans=max(ans,max(s[i-1]+r2[i+1],s[i-1]+r1[i+1]+(fg[pos[i]+1]&&!us[0][pos[i]+1]&&!us[3][pos[i]+1])));
		}
		else if(op[i]=='R'){
			ans=max(ans,max(s[i-1]+l2[i+1],s[i-1]+l1[i+1]+(fg[pos[i]-1]&&!us[0][pos[i]-1]&&!us[1][pos[i]-1])));
		}
		else{
			ans=max(ans,max(s[i-1]+l1[i+1],s[i-1]+r1[i+1]));
		}
	}
	printf("%d",ans);
	return 0;
}
```


---

