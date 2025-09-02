# 「Wdcfr-1」Alice Wins! (hard version)

## 题目描述

**版本之间的区别在于操作的限制。**

Alice 是一个可爱的女孩，她有很多玩偶。

有 $4\cdot n$ 个玩偶在玩“石头剪刀布”。它们被分成两个队伍：A 队和 B 队。每个队伍包含 $2\cdot n$ 个玩偶。

游戏将进行总共 $2\cdot n$ 轮。在第 $i$ 轮中，A 队的第 $i$ 个玩偶将与 B 队的第 $i$ 个玩偶对战。如果 A 队的玩偶赢了，A 队将获得 $1$ 分。如果输了，A 队将失去 $1$ 分。如果平局，A 队将不获得分数。

Alice 知道所有玩偶在这场游戏中的选择。具体来说，她使用两个数组 $a$ 和 $b$ 来表示两个队伍中玩偶的选择。$a_i$ 表示 A 队第 $i$ 个玩偶的选择，$b_i$ 表示 B 队第 $i$ 个玩偶的选择。在这个问题中，我们用 $1$ 表示石头，$2$ 表示剪刀，$3$ 表示布。

现在对于**每个队伍**，Alice 想要改变**恰好** $n$ 个玩偶的选择，以使 A 队的得分尽可能高。

找出 A 队的最大得分及其构造方法。如果有多个答案，输出任意一个（你仍然需要最大化 A 队的得分）。

## 说明/提示

### 解释

对于第一个测试用例，我们可以将 $a_2$ 改为 $1$，将 $b_1$ 改为 $2$。然后 A 队可以得到 $2$ 分。可以证明这是 A 队可以获得的最大分数。

### 约束

$1\le T,n \le 10^5; 1\le a_i,b_i \le 3$。所有测试用例的 $n$ 之和 $\le 10^5$。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
1
1
1 2
1 2```

### 输出

```
2
1 1
2 2```

# 题解

## 作者：tongyanmin (赞：4)

## Solution
由题意，我们必须恰好改变每队**恰好** $n$ 个人的出拳方案。即会出现在已经构造出全胜方案之后还有剩余的操作次数的情况。所以我们必须考虑如何构造，维持最终得分为 $2n$。

下面讲讲我的做法。

我们不妨定义修改 A 组的操作为操作 $x$，修改 B 组的操作为操作 $y$。

1. 依次使用操作 $x,y$，构造出 A 组全胜的状态。
2. 在经过上一步之后，可能存在操作次数还未用完的情况。对此我们不妨找出之前未被修改的对局（即 A 组本来就胜利的情况），同时对 $a_i,b_i$ 进行修改，使得两种操作的使用次数同时增加。
3. 经过以上两轮之后，可以发现要么已经构造完毕，要么还剩下一次 $y$ 操作（第 $1$ 步中可能会出现 $cnt_x=cnt_y+1$ 的情况）。对于这种情况，不妨找出第一次被修改的对局，对其使用一次 $y$ 操作即可。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[200005],b[200005],c[200005],d[200005];//把修改后的数存在数组c,d中
bool check(int x,int y){
	if(x==1&&y==2)return 1;
	if(x==2&&y==3)return 1;
	if(x==3&&y==1)return 1;
	return 0;
}//判断胜负
bool vis[200005];
int main(){
	cin>>t;
	while(t--){
		cin>>n;	
		int cnt=0,cntx=0,cnty=0;
		for(int i=1;i<=n*2;i++){
			cin>>a[i];
			c[i]=a[i];
			vis[i]=0;
		}
		for(int i=1;i<=n*2;i++){
			cin>>b[i];
			d[i]=b[i];
		}
		for(int i=1;i<=2*n;i++){
			if(check(a[i],b[i]))continue;
			cnt++;
			if(cnt%2==1){
				cntx++;
				c[i]=d[i]-1;
				if(c[i]==0)c[i]=3;
			}//改a
			else{
				cnty++;
				d[i]=c[i]+1;
				if(d[i]==4)d[i]=1;
			}//改b
			vis[i]=1;			
		}//改为a必胜的局面
		for(int i=1;i<=2*n;i++){
			if(vis[i])continue;
			if(cntx<n&&cnty<n){
				c[i]+=1;
				if(c[i]==4)c[i]=1;
				d[i]+=1;
				if(d[i]==4)d[i]=1;
				cntx++,cnty++;
			}
			if(cntx==cnty&&cntx==n)break;
		}//消耗多余的操作次数
		if(cnty<n){
			for(int i=1;i<=n*2;i++){
				if(vis[i]){
					for(int j=1;j<=3;j++){
						for(int k=1;k<=3;k++)
							if(j!=a[i]&&k!=b[i]&&check(j,k))c[i]=j,d[i]=k;
					}//此处直接暴力修改即可，记得判重
					break;
				}	
			}
		}
		cout<<n*2<<endl;
		for(int i=1;i<=n*2;i++)cout<<c[i]<<" ";
		cout<<endl;	
		for(int i=1;i<=n*2;i++)cout<<d[i]<<" ";
		cout<<endl;		
	}
	return 0;
}
```


---

## 作者：ahawzlc (赞：3)

思路： 简单贪心。

----

在 easy version 的基础上，hard version 将“至多”改成“恰好”。

其实是这两个题的贪心是一样的。先制造出 A 全胜的情况，然后只需要消耗操作次数就行。

所以我们还是前 n 次操作改 A 队，后 n 次操作改 B 队。如果 A 本来没赢，那么就进行修改，同时记录进行改动的队伍。全部改完后，有两种方式消耗修改次数：

1. A 本来就赢了，此时可以 A B 同时修改，消耗 A B 修改次数各一次。
2. A 或 B 改过了，那么可以重新修改两支队伍，消耗未修改的队伍的修改次数一次。

对于第二种情况，一定要注意修改后的情况和原来不能相同。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int N=200005;
int a[N],b[N],t,n;
int v1[N],v2[N];
int main() {
	scanf("%d",&t);
	while(t--) {
		scanf("%d",&n);
		for(int i=1; i<=n<<1; i++) scanf("%d",&a[i]),v1[i]=-1,a[i]--;
		for(int i=1; i<=n<<1; i++) scanf("%d",&b[i]),v2[i]=-1,b[i]--;
		int x=n,y=n;
		for(int i=1; i<=n; i++) if(a[i]!=(b[i]+2)%3) v1[i]=a[i],a[i]=(b[i]+2)%3,x--;
		for(int i=n+1; i<=n<<1; i++) if(a[i]!=(b[i]+2)%3) v2[i]=b[i],b[i]=(a[i]+1)%3,y--;
		for(int i=1; i<=n<<1; i++) {
			if(x&&y&&v1[i]==-1&&v2[i]==-1) {//方式1
				x--,y--,v1[i]=a[i],v2[i]=b[i];
				a[i]=(a[i]+1)%3,b[i]=(b[i]+1)%3;
				continue;
			}
			if(v1[i]==-1&&v2[i]!=-1&&x) {//方式2——A
				x--;
				v1[i]=a[i];
				while(a[i]==v1[i]||b[i]==v2[i]) a[i]=(a[i]+1)%3,b[i]=(b[i]+1)%3;
				continue;
			}
			if(v1[i]!=-1&&v2[i]==-1&&y) {//方式2——B
				y--;
				v2[i]=b[i];
				while(a[i]==v1[i]||b[i]==v2[i]) a[i]=(a[i]+1)%3,b[i]=(b[i]+1)%3;
				continue;
			}
		}
		printf("%d\n",n<<1);
		for(int i=1; i<=n<<1; i++) printf("%d ",a[i]+1);
		puts("");
		for(int i=1; i<=n<<1; i++) printf("%d ",b[i]+1);
		puts("");
	}
	return 0;
}
```

---

## 作者：joeger (赞：1)

## 题目大意。

给定两个长度为 $2n$ 的序列 $a$ 和 $b$，每个元素表示石头剪刀布的选择（$1 =$ 石头，$2 =$ 剪刀，$3 =$ 布）。要求恰好修改 $a$ 和 $b$ 各 $n$ 次，使得 $a$ 序列胜 $b$ 序列的局数最大化。



## 解题思路。

#### 分阶段处理：
- 阶段一：修改 $a$ 序列使恰好 $n$ 个 $a_i$ 能获胜。
- 阶段二：修改 $b$ 序列使对应的 $n$ 个 $b_i$ 确保失败。
- 阶段三：消耗剩余修改次数（如有）。

#### 胜负判断：使用模 3 运算判断胜负关系。

## 复杂度分析。
- 时间复杂度：$O(n)$ 只需遍历序列两次。
- 空间复杂度：$O(n)$ 需要存储两个序列。
- 算法效率：线性复杂度，适合大规模数据。

## Code。

```cpp
#include <iostream>
#include <vector>
using namespace std;

int check(int a, int b) {
    if(a == b) return 0;
    return (a % 3 + 1 == b) ? 1 : -1;
}

void solve() {
    int n;
    cin >> n;
    int m = 2 * n;
    vector<int> a(m), b(m);
    
    for(auto &x : a) cin >> x;
    for(auto &x : b) cin >> x;
    
    int wins = 0;
    for(int i = 0; i < m; i++)
        wins += (check(a[i], b[i]) == 1);
    
    // 阶段一：调整 a 序列
    for(int i = 0; i < m && n > 0; i++) {
        if(check(a[i], b[i]) != 1) {
            a[i] = (b[i] + 1) % 3 + 1;
            n--;
            wins++;
        }
    }
    
    // 阶段二：调整 b 序列
    for(int i = 0; i < m && n > 0; i++) {
        if(check(a[i], b[i]) != -1) {
            b[i] = (a[i] + 1) % 3 + 1;
            n--;
        }
    }
    
    // 输出结果
    cout << m << "\n";
    for(auto x : a) cout << x << " ";
    cout << "\n";
    for(auto x : b) cout << x << " ";
    cout << "\n";
}

int main() {
    int t;
    cin >> t;
    while(t--) solve();
    return 0;
}
```

---

## 作者：zzy0618 (赞：1)

### 题目大意

[题目链接](https://www.luogu.com.cn/problem/P7940)

两队人玩剪刀石头布，每队 $2n$ 个人，**分别**改变每队 $n$ 个人的出拳方案，使第一队得分最高。

### 大致思路

主要的思想是贪心，大体思路如下。

- 如果遇到第一组胜则先不操作。

- 如果遇到第一组没有胜利则轮流改变两组出拳（因为只要改一个就能保证第一组胜利）。

- 最终大概率有剩余的操作次数，则对未经改变的两组（也就是一开始就胜利的）同时改变，依然保持第一组胜利。

- 还有一种特殊情况，就是还剩下一次第二组的操作，则找到第一次对第一组的操作同时更改，将其消耗掉。

- 最终的得分一定是 $2n$。

由于剪刀石头布数值的改变与判断过于抽象，所以我们先将这些函数做出来。

1. 判断第一组是否胜利的函数

```cpp
bool win(int x, int y) {
	if (x == 1 && y == 2)return 1;
	if (x == 2 && y == 3)return 1;
	if (x == 3 && y == 1)return 1;
	return 0;
}
```

2. 对第一组改变的操作

```cpp
void change1(int x) {
	c[x] = d[x] - 1;//这里的c，d分别是改变后的第一，第二组。
	if (c[x] == 0)c[x] = 3;
}
```

3. 对第二组改变的操作

```cpp
void change2(int x) {
	d[x] = c[x] + 1;
	if (d[x] == 4)d[x] = 1;
}
```

4. 两组同时改变，消耗次数的操作

```cpp
void change3(int x) {
	c[x] += 1;
	d[x] += 1;
	if (c[x] == 4)c[x] = 1;
	if (d[x] == 4)d[x] = 1;
}
```

5. 最终处理特殊情况（还剩一次第二组操作）

```cpp
if (cnty < n) {
	for (int i = 1; i <= N; i++) 
		if (vis[i]) {
			for (int j = 1; j <= 3; j++) 
				for (int k = 1; k <= 3; k++)
					if (j != a[i] && k != b[i] && win(j, k))
						c[i] = j, d[i] = k;
			break;
		}
```

### 完整代码

由于题目的读入量巨大，使用快读还是很好的。

代码有点长，但很容易理解。

```cpp
#include<bits/stdc++.h>
using namespace std;
int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch>'9') {
		if (ch == '-')f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x * f;
}
int t, n, a[200005], b[200005], c[200005], d[200005];
// a，b为初始的第一，二组，c，d为改变后的一，二组 
bool vis[200005];//是否被改变 。
bool win(int x, int y) {
	if (x == 1 && y == 2)return 1;
	if (x == 2 && y == 3)return 1;
	if (x == 3 && y == 1)return 1;
	return 0;
}
void change1(int x) {
	c[x] = d[x] - 1;
	if (c[x] == 0)c[x] = 3;
}
void change2(int x) {
	d[x] = c[x] + 1;
	if (d[x] == 4)d[x] = 1;
}
void change3(int x) {
	c[x] += 1;
	d[x] += 1;
	if (c[x] == 4)c[x] = 1;
	if (d[x] == 4)d[x] = 1;
}
int main() {
	t = read();
	while (t--) {
		n = read();
		int cnt = 0, cntx = 0, cnty = 0, N = n * 2;
		//cnt：目前总操作次数，chtx：对第一组的操作次数，cnty：对第二组的操作次数。 
		//因为很多时候要用 n*2，所以把 n*2 先算出来，减少运算次数。 
		for (int i = 1; i <= N; i++) {
			a[i] = read();
			c[i] = a[i];
			vis[i] = 0;
		}
		for (int i = 1; i <= N; i++) {
			b[i] = read();
			d[i] = b[i];
		}
		for (int i = 1; i <= N; i++) {
			if (!win(a[i], b[i])) {
				cnt++;
				vis[i] = 1;
				if (cnt % 2 == 1) {
					cntx++;
					change1(i);
				}
				else {
					cnty++;
					change2(i);
				}//轮流使用一，二组的操作 。
			}
		}
		for (int i = 1; i <= N; i++) {
			if (!vis[i] && cntx < n && cnty < n) {
				change3(i);
				cntx++, cnty++;
			}
			if (cntx == n && cnty == n)break;
		}//消耗剩余操作次数 。
		if (cnty < n) {
			for (int i = 1; i <= N; i++) 
				if (vis[i]) {
					for (int j = 1; j <= 3; j++) 
						for (int k = 1; k <= 3; k++)
							if (j != a[i] && k != b[i] && win(j, k))
								c[i] = j, d[i] = k;
					break;
				}//特判，只要找到一种胜利且同时改变的方式即可。
		printf("%d\n", N);
		for (int i = 1; i <= N; i++)putchar(c[i] + '0'), putchar(' ');
		putchar('\n');
		for (int i = 1; i <= N; i++)putchar(d[i] + '0'), putchar(' ');
		putchar('\n');
		//因为输出除了 n*2，其他只有 1,2,3，一个字符，用 putchar 更快 。
	}
	return 0;
}
```

---

## 作者：Dark_Blue_Sky (赞：1)

# P7940

## 分析

1. A 没赢，则消耗一次次数修改，使 A 赢（两队任意一个皆可）。
2. 改完后，两队各消耗一次次数，使 A 本来就赢的情况，让 A 继续赢。
3. 最终的答案一定是 $2n$。

---

## 作者：LG086 (赞：0)

两个数列，每个数列要恰好改 $n$ 次，求最大得分。


贪心。我们先控制刚好 $n$ 个 $a_i$ 胜，随后可以让另外 $n$ 个 $a_i$ 对应的 $b_i$ 输。这样最终答案一定是 $2n$。



因为 $1$ 表示石头，$2$ 表示剪刀，$3$ 表示布，所以我们有如下函数返回结果。

```cpp
int ck(int pa, int pb) {
  if (pa == pb)
    return 0;//平
  if (pa % 3 + 1 == pb)
    return 1;//a 胜
  return -1;//a 败
}
```

其中 $pa$ 和 $pb$ 分别表示两个人的选择。


先数出一开始赢几局，记作 $ans$。

分情况讨论 $ans = n$ 时，$ans > n$ 时和 $ans < n$ 时。  
若 $ans = n$，则控制其他 $n$ 个 $a_i$ 不赢。  
若 $ans > n$，则控制只有 $n$ 个 $a_i$ 胜利，并再修改 $2n-ans$ 个 $a_i$，还有保证修改后这些 $a_i$ 仍不赢。  
若 $ans < n$，则保证 $n$ 个 $a_i$ 胜利，并再修改 $ans$ 个 $a_i$，需要保证修改后这些 $a_i$ 仍不赢。

这样每个 $b_i$ 就是与 $a_i$ 相对应的值。



下面给出示例代码。

```cpp
int ans = 0;
int m = n * 2;
int n1 = 0, n2 = 0;
for (int i = 1; i <= m; i++)
  cin >> a[i];
for (int i = 1; i <= m; i++)
  cin >> b[i], ans += (ck(a[i], b[i]) == 1);
if (ans == n) {
  for (int i = 1; i <= m; i++)
    chg(i);
} else if (ans > n) {
  for (int i = 1; i <= m; i++)
    if (ck(a[i], b[i]) == 1 and ans > n)
      a[i] = b[i] % 3 + 1, ans--, n1++;
    else if (n1 < n)
      if (ck(a[i], b[i]) != 1)
        n1++, chg(i);
} else {
  for (int i = 1; i <= m; i++)
    if (ck(a[i], b[i]) != 1 and ans < n)
      a[i] = (b[i] + 1) % 3 + 1, ans++, n2++;
    else if (n2 < n)
      if (ck(a[i], b[i]) != 1)
        n2++, chg(i);
}
cout << (m) << "\n";
for (int i = 1; i <= m; i++)
  cout << a[i] << " ";
cout << "\n";
for (int i = 1; i <= m; i++)
  cout << a[i] % 3 + 1 << " ";
cout << "\n";
```

---

## 作者：Wish_kazdel (赞：0)

## 思路

与简单版的区别就是困难版是会恰好改变 $n$ 个人的出拳方式。其实做法就是先计算出 A 队伍全部获胜情况。如果获胜次数不等于 $n$ 时，则修改方案将获胜数刚好修改为 $n$。而如果获胜数等于 $n$ 时，则将此时未获胜的情况修改为另一种即可。

而此时 B 队就不用再多进行考虑，因为所有情况我们均已解决了。

---

## 作者：joker_opof_qaq (赞：0)

## 题意简述

两队人玩剪刀石头布，每队 $2n$ 个人，分别改变每队 $n$ 个人的出拳方案，使第一队得分最高。

## 思路

贪心。


- A 队赢了，则先不操作。
  
- 如果遇到 A 没有胜利则轮流改变两组出拳（因为只要任意改一个就能保证第一组胜利）。

- 最终剩余的次数，就对未经改变即 A 胜情况同时改变，不影响答案。

- 最终答案肯定是 $2n$。

---

## 作者：Amunet (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P7940)

# 题目大意

两队人玩剪刀石头布，每队 $2 \times n$ 个人，分别改变每队 $n$ 个人的出拳方案，使第一队得分最高。

# 题目分析

在 easy version 上，hard version 将至多改成恰好。

贪心，先制造出 A 队全胜的情况，然后消耗操作次数就行。

还是前 $n$ 次操作改 A 队，后 $n$ 次操作改 B 队。如果 A 队没赢，就进行修改，记录改了的队伍。改完后，有两种方式使用修改次数：

1. A 队赢了，将 A 队，B 队同时修改，同时使用 A，B 修改次数各一次。

2. A 队或 B 队改过了，那么从头改两支队伍，使用没改的队伍的修改次数一次。

要注意，第二种，修改后的情况必须和原来不同。

---

