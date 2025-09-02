# [ABC391C] Pigeonhole Query

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc391/tasks/abc391_c

$ N $ 匹の鳩がおり、 $ 1 $ から $ N $ までの番号がつけられています。また、 $ N $ 個の巣があり、 $ 1 $ から $ N $ までの番号がつけられています。はじめ、鳩 $ i $ は巣 $ i $ にいます $ (1\leq\ i\leq\ N) $。

$ Q $ 個のクエリが与えられるので順に処理してください。 クエリは $ 2 $ 種類あり、以下のいずれかの形式で与えられます。

- `1 P H` : 鳩 $ P $ を巣 $ H $ に移動させる。
- `2` : 複数の鳩がいる巣の個数を出力する。

## 说明/提示

### 制約

- $ 2\leq\ N\leq\ 10^6 $
- $ 1\leq\ Q\leq\ 3\times\ 10^5 $
- $ 1\leq\ P,H\leq\ N $
- $ 1 $ つ目の形式のクエリについて、鳩 $ P $ は移動する前に巣 $ H $ にいない
- 入力は全て整数
 
### Sample Explanation 1

初め、鳩 $ 1,2,3,4 $ はそれぞれ巣 $ 1,2,3,4 $ にいます。 - $ 1 $ つ目のクエリについて、巣 $ 1,2,3,4 $ にはそれぞれ $ 1,1,1,1 $ 匹います。鳩が複数いる巣は存在しないので $ 0 $ を出力します。 - $ 2 $ つ目のクエリについて、鳩 $ 1 $ を巣 $ 2 $ に移動します。 - $ 3 $ つ目のクエリについて、巣 $ 1,2,3,4 $ にはそれぞれ $ 0,2,1,1 $ 匹います。鳩が複数いる巣は巣 $ 2 $ の $ 1 $ つなので $ 1 $ を出力します。 - $ 4 $ つ目のクエリについて、鳩 $ 3 $ を巣 $ 2 $ に移動します。 - $ 5 $ つ目のクエリについて、巣 $ 1,2,3,4 $ にはそれぞれ $ 0,3,0,1 $ 匹います。鳩が複数いる巣は巣 $ 2 $ の $ 1 $ つなので $ 1 $ を出力します。 - $ 6 $ つ目のクエリについて、鳩 $ 3 $ を巣 $ 4 $ に移動します。 - $ 7 $ つ目のクエリについて、巣 $ 1,2,3,4 $ にはそれぞれ $ 0,2,0,2 $ 匹います。鳩が複数いる巣は巣 $ 2,4 $ の $ 2 $ つなので $ 2 $ を出力します。

## 样例 #1

### 输入

```
4 7
2
1 1 2
2
1 3 2
2
1 3 4
2```

### 输出

```
0
1
1
2```

## 样例 #2

### 输入

```
5 10
2
1 4 3
1 4 5
2
1 3 1
2
1 2 3
1 2 5
1 1 3
2```

### 输出

```
0
1
2
1```

# 题解

## 作者：ikunTLE (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc391_c)

### 思路

首先用 $A_i$ 代表第 $i$ 个鸟巢里有多少只鸽子，$T_i$ 代表第 $i$ 只鸽子在哪个鸟巢里。故初始化 $A_i=1$，$T_i=i$。

然后模拟。初始化答案计数器 $C=0$。

- 若进行操作 $1$：
  - 先模拟鸽子飞出去，即 $A_{T_P}\gets A_{T_P}-1$。若此时 $A_{T_P}=1$，说明这个鸟巢由多只鸽子变为单只鸽子，$C\gets C-1$。
  - 再模拟鸽子飞进来，即 $A_H\gets A_H+1$。若此时 $A_H=2$，说明这个鸟巢由单只鸽子变为多只鸽子，$C\gets C+1$。同时更改 $T_P=H$，代表第 $P$ 只鸽子飞进了第 $H$ 个鸟巢。
- 若进行操作 $2$：输出答案计数器 $C$ 即可。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=1e6+10;
int a[N],p[N];
signed main(){
	int n=read(),q=read();
	for(int i=1;i<=n;++i)
		a[i]=1,p[i]=i;
	int cnt=0;
	while(q--){
		int op=read();
		if(op==1){
			int x=read(),y=read();
			--a[p[x]];
			if(a[p[x]]==1)
				--cnt;
			p[x]=y,++a[y];
			if(a[y]==2)
				++cnt;
		}
		else printf("%d\n",cnt);
	}
	return 0;
}
```

---

## 作者：FlowerAccepted (赞：3)

介绍两种解法，还是第二种简便。

# Solution 1

## 解题思路

我们可以维护每个鸽子在哪个巢穴（${\tt int} \space pigeon[MAXN]$），每个巢穴里有哪些鸽子（${\tt std::map} \space nest[MAXN]$），以及答案 $cnt$。

初始化时，

$$
\forall 1 \le i \le n \\
\begin {aligned}
nest_{i, i} &= \color{#00dd00}{true} \\
pigeon_i &= i
\end {aligned}
$$

对于每个 `1` 操作，注意到当且仅当要移出鸽子的巢穴刚好有两只鸽子时，移出鸽子后答案会减一；要移入鸽子的巢穴刚好有一只鸽子时，移入鸽子后答案会加一。

于是先判断

```cpp
if (nest[pigeon[N]].size() == 2) {；
    cnt --;
}
if (nest[P].size() == 1) {
    cnt ++;
}
```

然后删除原来巢穴中的鸽子

```cpp
auto it = nest[pigeon[N]].find(N);
nest[pigeon[N]].erase(it);
```

并重新分配鸽子的位置

```cpp
pigeon[N] = P;
nest[P][N] = 1;
```

对于每个 `2` 操作，输出 $cnt$ 并**换行**即可。

## 代码呈现

```cpp
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <map> // 不用万能头
using namespace std;

map<int, bool> nest[1000005];
int pigeon[1000005]; // 开大

int main() {
    int n, q, cnt, op, N, P;
    cin >> n >> q;
    cnt = 0;
    for (int i = 1; i <= n; i ++) {
        nest[i].clear();
        nest[i][i] = 1;
        pigeon[i] = i; // 初始化
    }
    for (int i = 1; i <= q; i ++) {
        cin >> op;
        if (op == 1) {
            cin >> N >> P;
            if (nest[pigeon[N]].size() == 2) { // 要移出鸽子的巢穴刚好有两只鸽子，减去一只就会使答案减一
                cnt --;
            }
            if (nest[P].size() == 1) { // 要移入鸽子的巢穴刚好有一只鸽子，加上一只就会使答案加一
                cnt ++;
            }
            auto it = nest[pigeon[N]].find(N);
            nest[pigeon[N]].erase(it); // 删除鸽子
            pigeon[N] = P; // 定位
            nest[P][N] = 1; // 添加鸽子
        } else {
            cout << cnt << '\n';
        }
    }
    return 0;
}

```

至此，此题 Accepted。

## 复杂度分析

$\tt std::map$ 的时间复杂度是 $O(\log n)$，程序的时间复杂度是 $O((N + Q) \log N)$，可过

# Solution 2

## 解题思路

赛时想出的解法一，难免有些不足。

注意到，在解法一中，没有必要存巢穴里的每个鸽子，存数量即可。

## 代码呈现

```cpp
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <map> // 不用万能头
using namespace std;

int nest[1000005], pigeon[1000005]; // 开大

int main() {
    int n, q, cnt, op, N, P;
    cin >> n >> q;
    cnt = 0;
    for (int i = 1; i <= n; i ++) {
        nest[i] = 1;
        pigeon[i] = i;
    }
    for (int i = 1; i <= q; i ++) {
        cin >> op;
        if (op == 1) {
            cin >> N >> P;
            if (nest[pigeon[N]] == 2) { // 要移出鸽子的巢穴刚好有两只鸽子，减去一只就会使答案减一
                cnt --;
            }
            if (nest[P] == 1) { // 要移入鸽子的巢穴刚好有一只鸽子，加上一只就会使答案加一
                cnt ++;
            }
            nest[pigeon[N]] --; // 删除鸽子
            pigeon[N] = P; // 定位
            nest[P] ++; // 添加鸽子
        } else {
            cout << cnt << '\n';
        }
    }
    return 0;
}

```

## 复杂度分析

去掉 $\tt std::map$，代码的时间复杂度是 $O(N + Q)$，更优化了。

---

## 作者：C_0_a4S (赞：2)

### 题意
有 $N$ 只鸽子和 $N$ 个巢，最开始，第 $i$ 只鸽子在第 $i$ 个巢内 $(1 \le i \le N)$。

你需要处理 $Q$ 个询问，分两种：

- `1 P H` 将第 $P$ 只鸽子移到第 $H$ 个巢。
- `2` 输出有超过一只鸽子的巢的数量。
### 解法
我们可以开两个 `unordered_map`，一个为 $a$，一个为 $b$，再开一个变量 $cnt$ 存储有超过一只鸽子的巢的数量（初始值为 $0$）。

$a$ 用于存储每个巢里鸽子的数量，$b$ 用于存储每个鸽子在哪个巢。

进行操作 $1$ 时将 $a_{p_{h}}$ 减少 $1$，并将 $b_{h}$ 增加 $1$。同时要判断有超过一只鸽子的巢的数量是否增加或者减少并修改 $cnt$。

进行操作 $2$ 时直接输出 $cnt$ 即可。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
unordered_map<int,int>a;
unordered_map<int,int>b;
int cnt=0;
int main(){
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		a[i]=1;
		b[i]=i;
	}
	while(q--){
		int opt;
		cin>>opt;
		if(opt==1){
			int p,h;
			cin>>p>>h;
			a[b[p]]--;
			if(a[b[p]]==1)	cnt--;
			b[p]=h;
			a[h]++;
			if(a[h]==2)	cnt++; 
		}
		else{
			cout<<cnt<<'\n';
		}
	}
}
```

---

## 作者：XXh0919 (赞：2)

~~嗨嗨嗨，又是我最喜欢的操作题。~~

### 题意

有 $N$ 只鸽子和 $N$ 个笼子。初始第 $i$ 只鸽子在第 $i$ 个笼子里。有两个操作：

- `1 P H`：表示将第 $P$ 只鸽子移动到第 $H$ 个笼子里。
- `2`：表示查询有多少个笼子里的鸽子数量**大于** $1$ 只。

### 解法

首先我们可以很容易想到用一个桶来存储每一个笼子里面的鸽子数量，即令 $t_i$ 表示第 $i$ 个笼子里的鸽子数量。接着看两个操作，直接模拟肯定会爆炸，所以我们可以预处理出每一只鸽子所处笼子的编号和此时有多少笼子里的鸽子数量大于 $1$ 只，那我们令 $l_i$ 表示第 $i$ 只鸽子在第 $l_i$ 号笼子里，$ans$ 表示操作二的答案。那么这两个操作我们可以直接这样做：
```cpp
int pre = l[p];//第 p 只鸽子的笼子编号
t[pre] --;//这只鸽子所处笼子里少一只鸽子
if (t[pre] == 1) -- ans;//为了避免重复计算，必须取等于
t[h] ++;//第 h 个笼子里多一只鸽子
if (t[h] == 2) ++ ans;//同理
l[p] = h;//第 p 只鸽子移动到第 h 个笼子里
```
所以代码就出来了。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int N = 1e6 + 15;

const int I_LOVE_CCF = 1;

int n, q;
int t[N], l[N];
int ans;

inline int read (int &n) {
	int x = 0, f = 1;
	char ch = getchar ();
	while (! isdigit (ch)) {
		if (ch == '-') f = -1;
		ch = getchar ();
	}
	while (isdigit (ch)) {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar ();
	}
	n = x * f;
	return n;
}



signed main () {
	read (n), read (q);
	rep (i, 1, n) t[i] = 1, l[i] = i;
	while (q --) {
		int op;
		read (op);
		if (op == 1) {
			int p, h;
			read (p), read (h);
			int pre = l[p];
			t[pre] --;
			if (t[pre] == 1) -- ans;
			t[h] ++;
			if (t[h] == 2) ++ ans;
			l[p] = h;
		}else printf ("%lld\n", ans);
	}
	return 0;
} 
```

---

## 作者：天使宝贝 (赞：2)

[题面传送门](https://www.luogu.com.cn/problem/AT_abc391_c)

### 题目大意
有 $n$ 只鸽子在 $n$ 个巢穴中，鸽子与巢穴的编号从 $1$ 到 $n$。

有 $q$ 次操作：

* `1 P H` ：将编号为 $P$ 的鸽子移动到巢穴 $H$。
* `2`：输出含有多只鸽子的巢穴数量。

### 思路&分析
我们可以记录编号为 $i$ 的鸽子目前在哪个巢穴，并求出每个巢穴中鸽子的数量，然后在求每个巢穴中鸽子数量的同时，用一个计数变量求出有多少巢穴含有多只鸽子，记为 $cnt$。对于每次操作 $1$，判断是否会对 $cnt$ 产生影响，如果产生了，就修改 $cnt$。

编码注意点：在写判断时，需要防止多判或漏盘，~~我就是那个多判的人~~。

### CODE
[赛时代码](https://atcoder.jp/contests/abc391/submissions/62277209)

---

## 作者：ryf2011 (赞：2)

# 题目思路
对于本题，原本想用暴力，但 $N$ 的范围过大，直接模拟会导致超出时限，所以，我们考虑优化整个过程。

首先，我们注意到以 $N$ 的范围开数组还不足以导致内存超限，所以我们开一个数组记录当前每个位置鸽子的个数，同时，我们还要开一个布尔类型的数组，记录当前位置对答案是否还有贡献，并实时更新，每个位置有两种状态，即无贡献和有贡献。再用一个变量记录答案。

我们先考虑情况一，即移动鸽子。

要注意：题意是把鸽子 $P$ 移动到 $H$ 这个位置,并不是把位置 $P$ 中的一个鸽子移动到 $H$ 这个位置。

我们要用一种方法记录每个鸽子的当前位置信息，对于本题，作者用了一个结构体记录了鸽子的编号和当前位置信息，其中记录编号并没有作用，因为记录当前位置后，鸽子在此结构体中的位置并未变化。

当鸽子 $P$ 的当前位置所指的位置的鸽子个数小于 $1$ 并且所指位置曾对答案做出贡献，说明之前答案曾记录过它的贡献，此时答案减 $1$ 并让所指位置重设为无贡献这一状态。

然后，我们将编号为 $P$ 的鸽子的当前位置设为 $H$ 这个值，然后再将 $H$ 所指位置的鸽子个数加 $1$ 即可。

当然，我们还要判断 $H$ 所指位置鸽子个数是否大于 $1$ 且此位置之前是否未对答案作出贡献，如果都成立，说明答案之前未记录此位置的贡献，让答案加 $1$ 并让所指位置重设为有贡献这一状态。

我们再来考虑情况二，即输出答案。

由于数据很大，我们如果不在情况一时计算答案，而在这时暴力寻找的话，容易超出时限。所以我们只要在情况一时计算答案，此时直接输出即可。

# 代码
注：本代码并非最简单的写法，仅供参考，明确思路即可。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,q,p,h,op,nums[1000005],ans; //nums[i]:位置 i 有几只鸽子 
bool forans[1000005]; //记录每个位置对答案是否还有贡献 
struct node{
	int id; //编号 
	int l; //当前所在位置 
} pigeons[1000005]; //结构体记录每只鸽子的有关信息 
int main(){
	scanf("%d %d",&n,&q); //输入 
	for(int i=1;i<=n;i++){ //将所有鸽子信息初始化 
		pigeons[i].id=i;
		pigeons[i].l=i;
	}
	for(int i=1;i<=q;i++){
		scanf("%d",&op);
		if(op==1){ //移动 
			scanf("%d %d",&p,&h);
			nums[pigeons[p].l]--; //注意：不是改变 p 所指位置的值，而是改变编号为 p 的鸽子的当前位置这个位置的值 
			if(nums[pigeons[p].l]<1&&forans[pigeons[p].l]==true){ //此位置之前做出了贡献，但现在已不能再作出贡献（即不满足条件），那么答案 -1 
				if(ans>0){ //防止答案变量为负数 
					ans--;
				}
				forans[pigeons[p].l]=false; //重置为 “无贡献 ” 
			}
			pigeons[p].l=h; //将编号为 p 的鸽子的当前位置重设为 h 
			nums[h]++; //由题意可知 
			if(nums[h]>0&&forans[h]==false){ //与上文代码同理，如果这个位置之前没有对答案作出贡献，但现在能作出贡献（即满足条件），那么答案 +1 
				ans++;
				forans[h]=true; //重置为 “有贡献 ” 
			}
		}
		else{ //输出答案 
			printf("%d\n",ans);
		}
	}
	return 0;
}
```

#### 后记
更多内容，请移步至 [$\color{red}\texttt{ryf2011}$](https://www.luogu.com.cn/user/1151973 "点我进入ryf2011")。

---

## 作者：CleverLiu (赞：1)

## 题目大意
有 $N$ 只鸽子及鸽巢，编号从 $1$ 到 $N$。最初，鸽子 $i$ 在 $1\leq i\leq N$ 的巢 $i$ 中。  
您会收到 $Q$ 次询问。询问有两种类型，每种都以下列格式之一给出：
- `1 P H` : 将鸽子 $P$ 移到鸽巢 $H$。
- `2` : 输出包含一只以上鸽子的鸽巢数量。

## 解题思路
考虑直接模拟，开两个数组。分别储存鸽子 $v_i$ 所在的鸽巢 $mp_i$，以及鸽巢 $mp_i$ 中的鸽子数。

- 对于询问 $1$，直接将 $v_p$ 赋值为 $h$ 即可。
- 对于询问 $2$，统计共有多少个鸽巢的鸽子数量大于 $1$。

由于数据范围中：
> $2 \leq N \leq 10^6$  
> $1 \leq Q \leq 3\times 10^5$  
> $1 \leq P, H \leq N$

直接遍历数组必然超时，考虑优化。

定义一个 $cnt$ 变量，在每次鸽巢的状态变化时（即询问 $1$），检查其鸽子数量是否变化为大于一只或小于一只，如果是，相应的对 $cnt$ 的值进行改变。

至此，这题完成。

## 代码实现

```cpp
//(AtCoder Beginner Contest 391)(atcoder) C - Pigeonhole Query
#include<bits/stdc++.h>
using namespace std;

const int N=1e6+10;
int n, q, ask, p, h, cnt=0;//cnt变量统计
int mp[N], v[N];//mp储存鸽巢中的鸽子数，v储存鸽子i所在的鸽巢

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	cin >> n >> q;
//初始化，第i只鸽子在第i个鸽巢，每个鸽巢一开始有i只鸽子
	for(int i=1; i<=n; i++) {
		v[i] = i;
		mp[i] = 1;
	}
	while(q--) {
		cin >> ask;
		if(ask==1) {
			cin >> p >> h;
            //鸽子p原先所在的鸽巢鸽子数减一
			mp[v[p]]--;
			//如果鸽巢里的鸽子由大于一只变为一只，cnt减一
			if(mp[v[p]]==1) {
				cnt--;
			}
			v[p] = h;
            //鸽子p现在所在的鸽巢鸽子数加一
			mp[v[p]]++;
			//如果鸽巢里的鸽子由一只大于一只，cnt加一
			if(mp[v[p]]==2) {
				cnt++;
			}
		}
		else {
            //操作二，直接输出
			cout << cnt << '\n';
		}
	}
	return 0;
}
```

---

## 作者：wuzebang2009 (赞：1)

## 思路：
题目意思很简单，把第 $P$ 只鸟移到鸟笼 $H$ 每次询问几个鸟笼个数大于 $1$ 。

设答案为 $ans$ ，我们只需要记录每只鸟所在的鸟笼，再记录哪个被取走鸟的鸟笼鸟的数量等于 $1$ ，则 $ans-1$ ，如果有一个鸟笼刚加一只鸟并且这个鸟笼鸟的数量等于 $2$ ，则 $ans+1$ 。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q;
bool vis[1000010];
map<int,int> mp;
int a[1000010];

int main(){
    cin>>n>>q;
    int ans=0;
    for(int i=1;i<=n;i++) mp[i]=i,a[i]=1;
    while(q--){
        int op;
        cin>>op;
        if(op==1){
            int p,h;
            cin>>p>>h;
            a[mp[p]]--;
            a[h]++;
            if(a[mp[p]]==1)ans--;
            mp[p]=h;
            if(a[h]==2)
                ans++;
        }
        if(op==2){
            cout<<ans<<endl;
        }
    }
}
```

---

## 作者：crz_qwq (赞：1)

对每个鸽巢记录里面的鸽子数量和每个鸽子在哪个巢穴里。

修改时可以将鸽子 $x$ 所在的巢穴里的鸽子数量 $y$ 减去 $1$，将新巢穴的鸽子数量 $z$ 加上 $1$，然后统计。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int fa[N],cnt[N],ans;
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;++i)
    {
        fa[i]=i;
        cnt[i]=1;
    }
    while(m--)
    {
        int op,x,y;
        cin>>op;
        if(op==1)
        {
            cin>>x>>y;
            --cnt[fa[x]];
            if(cnt[fa[x]]==1)
                --ans;
            fa[x]=y;
            ++cnt[fa[x]];
            if(cnt[fa[x]]==2)
                ++ans;
        }
        else
            cout<<ans<<'\n';
    }
}
```

---

## 作者：Cosine_Func (赞：1)

简单模拟题。开两个数组记录鸽巢中的鸽子数量和每只鸽子所在鸽巢的编号，进行操作时判断鸽子数量并修改答案。单次操作复杂度 $O(1)$，整个算法的时间复杂度 $O(N+Q)$。

核心代码如下：
```cpp
int n,q,ans,pos[N],cnt[N];
inline void Solve(){
	cin>>n>>q;
	ans=0;
	for(int i=1;i<=n;i++)
		pos[i]=i,cnt[i]=1;
	while(q--){
		int op,p,h;
		cin>>op;
		if(op==1){
			cin>>p>>h;
			cnt[pos[p]]--;
			cnt[h]++;
			if(cnt[pos[p]]==1)ans--;
			if(cnt[h]==2)ans++;
			pos[p]=h;
		}
		if(op==2){
			cout<<ans<<endl;
		}
	}
}
```
[参考代码](https://atcoder.jp/contests/abc391/submissions/62269079)

---

## 作者：15805856563fqm (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc391_c)

题目给你 $n$ 个鸽子巢，然后给出两种操作，让你求每次询问 $2$ 时有几个鸽子巢至少有两个鸽子。

当执行 $1$ 操作，我们需要把鸽子 $P$ 移动到巢 $H$，不难看出，我们只需在操作的时候计算答案即可。 

设 $b_i$ 为鸽子 $i$ 在的巢，设 $t_i$ 为巢 $i$ 飞走的鸽子的数，设 $B_i$ 为巢 $i$ 当前的状态。在统计增加的答案时，只需减去对应的 $t_i$，然后如果它已经记录过，那么不动答案，否则答案加一并记录。

然后在把 $t_{b_x}$ 加一，表示 $x$ 的上一个巢飞走了 $x$。

然后统计减小的答案，与增加大致一样，如果它被记录过，就把答案减一，然后取消记录。

code：

```
#include<iostream>
#include<algorithm>
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,cnt;
int b[1000001],B[1000001];
vector<int>a[1000001];
int t[1000001];
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)a[i].push_back(i),b[i]=i;
	while(m--){
		int op;
		cin>>op;
		if(op==1){
			int x,y;
			cin>>x>>y;
			a[y].push_back(x);
			if(a[y].size()-t[y]>1&&B[y]==0)cnt++,B[y]=1;
			
			t[b[x]]++;
			
			if(a[b[x]].size()-t[b[x]]<2&&B[b[x]]==1){cnt--;B[b[x]]=0;}
			b[x]=y;
		}else{
			cout<<cnt<<endl;
		}
	}
	return 0;
}
```

---

## 作者：chaqjs (赞：1)

## question

有 $N$ 只鸽子，编号从 $1$ 到 $N$，有 $N$ 个鸽巢，编号从 $1$ 到 $N$。最初，鸽子 $i$ 在巢 $i(1\leq i\leq N)$ 中。

您会收到 $Q$ 个查询，您必须按顺序处理这些查询。查询有两种类型，每种都以下列格式之一给出：

* `1 P H` ：将鸽子 $P$ 移到鸽巢 $H$ 中。
* `2` ：输出包含一只以上鸽子的鸽巢数量。

## solution

首先我们解决操作 $1$。

我们让 $a_i$ 表示巢 $i$ 的鸽子数量，同时让 $b_i$ 表示鸽子 $i$ 目前所处的巢相对于初始的巢 $i$ 偏移了多少。

那么我们可以得到以下代码。

    if (opt == 1){
        int p, h;
        cin >> p >> h;
        int now = p + b[p];// 鸽子 p 目前所处的巢的编号为 now
        a[now]--;
        a[h]++;
        b[p] = h - p;// 更新b[i]
    }

接下来我们考虑操作 $2$。

显然不能每次的扫一遍 $a$ 数组，所以我们在操作 $1$ 中加一步。对于每次操作 $1$，有可能对答案做出贡献的只有 $a_{now}$ 和 $a_h$，所以我们进行分类讨论。

* 若 $a_{now}$ 操作完后等于 $1$，则说明 $a_{now}$ 操作之前一定符合条件，那么我们让答案减 $1$。
  
* 若 $a_h$ 操作完后大于 $1$，且 $a_h$ 操作之前不符条件，那么我们让答案加 $1$。
  

为了方便，我们记录 $f_i$ 表示巢 $i$ 当前是否符合条件。整体思路出来了，以下是完整代码。

    #include <bits/stdc++.h>
    using namespace std;
    
    #define int long long
    
    const int N = 1e8 + 5;
    
    int n, q; 
    int a[N], b[N];
    int cnt;
    bool f[N];
    
    signed main(){
        cin.tie(0)->sync_with_stdio(0);
    
        cin >> n >> q;
    
        for (int i = 1; i <= n; i++)// 给 a 数组付赋初值
            a[i] = 1;
    
        while (q--){
            int opt;
            cin >> opt;
            if (opt == 1){
                int p, h;
                cin >> p >> h;
                int now = p + b[p];
                a[now]--;
                a[h]++;
                b[p] = h - p;
                if (a[now] == 1) cnt--, f[now] = 0;
                if (a[h] > 1 && !f[h]) cnt++, f[h] = 1;
            }
            else if (opt == 2)
                cout << cnt << "\n";
        }
    
        return 0;
    }

---

## 作者：违规用户名1053866 (赞：1)

我们先要定义一个 $a$ 数组、一个 $cnt$ 数组和一个 $ans$ 变量，分别表示每只鸽子所在的位置、每个巢穴中有几只鸽子和当前符合题目要求的巢穴数量。一开始 $a_i=i$，$cnt_i=1$。

考虑在每一次操作后统计答案变化。需要变化的情况有两种：

1. $cnt_{a_p}$ 不等于二，并且 $cnt_h$ 等于一。这样，巢穴 $h$ 中鸽子数量达到了两只，鸽子 $p$ 原本所在的巢穴中如果原来只有一只或达到了三只，都不会影响答案，所以这种情况下 $ans+1$。
2. $cnt_{a_p}$ 等于二，并且 $cnt_h$ 不等于一。这种情况下鸽子 $p$ 原本所在的巢穴中只剩下一只鸽子，$ans-1$。

每次操作结束后变动两个巢穴中的鸽子数量以及 $a_p$，也就是 $cnt_{a_p}$ 减一，$cnt_h$ 加一，再把 $a_p$ 更改为 $h$。

要输出时，直接输出 $ans$ 即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,x,p,h,a[2000005],cnt[2000005],ans;
int main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		a[i]=i;
		cnt[i]=1;
	}
	while(q--){
		cin>>x;
		if(x==1){
			cin>>p>>h;
			if(cnt[a[p]]!=2&&cnt[h]==1)
				ans++;
			if(cnt[a[p]]==2&&cnt[h]!=1)
				ans--;
			cnt[a[p]]--;
			cnt[h]++;
			a[p]=h;
		}
		else
			cout<<ans<<"\n";
	}
}
```

---

## 作者：Tiger_Rory (赞：0)

主要思路：实时记录每个鸽子所在的巢穴，并且实时记录每个巢穴的鸽子总量进行答案的加减就做完了。

参考代码如下（有一点细节）。


```cpp
#include<bits/stdc++.h>
using namespace std;

int n,q;
int h[1000005],fa[1000005];
//h数组代表巢穴里的鸽子总量,fa数组代表每个鸽子所在的巢穴 

int main() {
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>q; 
	int op,i,ans=0;
	for(i=1;i<=n;i++)h[i]=1,fa[i]=i; //初始化 
	while(q--) {
		cin>>op; 
		if(op==1) {
			int p,x; cin>>p>>x;
			bool ok=1; 
			if(h[x]<=1) ok=0;//修改前没有记进答案，那增多后就可能记进答案  
			h[x]++;//更新鸽子数 
			if(h[x]>1&&!ok) ++ans;//修改前没有记进答案且现在可以记录进去 
			ok=1; 
			if(h[fa[p]]>1) ok=0;//修改前记进答案，那减少后可能踢出答案 
			h[fa[p]]--;//更新鸽子数 
			if(h[fa[p]]<=1&&!ok)--ans;//修改前记进答案且现在被踢出 
			fa[p]=x; //更新鸽子的巢穴 
		}
		else {
			cout<<ans<<'\n'; 
		}
	}
	return 0;
}
```

如有不足，还请指出，谢谢大家。

---

## 作者：linjinkun (赞：0)

发现每一次操作只会使答案加 $1$ 或减 $1$ 或者不变，于是直接用一个 $mp$ 数组记录每一只鸽子在第几号巢穴，以及一个 $num$ 数组表示每个巢穴有多少只鸽子，然后按题意模拟即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6+5;
int num[N];
int mp[N];
signed main()
{
    int n,q;
    scanf("%d %d",&n,&q);
    for(int i = 1;i<=n;i++)
    {
        num[i] = 1;
        mp[i] = i;
    }
    int ans = 0;
    while(q--)
    {
        int opt;
        scanf("%d",&opt);
        if(opt == 1)
        {
            int x,y;
            scanf("%d %d",&x,&y);
            num[mp[x]]--;
            if(num[mp[x]] == 1)
            {
                ans--;
            }
            num[y]++;
            if(num[y] == 2)
            {
                ans++;
            }
            mp[x] = y;
        }
        else
        {
            printf("%d\n",ans);
        }
    }
    return 0;
}
```

---

## 作者：Ybw0731 (赞：0)

## 前言
爆炸了，这周的三场比赛两场没有切出黄题，但介于 AT 棕名了，发个题解纪念一下。
## 思路
一看数据范围，就知道这一题肯定是线性复杂度，我们需要先预处理出每一个鸽子在哪个鸽笼和每个鸽笼里有几只鸽子，然后，当鸽子飞走到其他笼子时，就可以开始计算有几个鸽笼里有多只鸽子。计算也很简单，如果这只鸽子老的鸽笼里只有了一只鸽子，那么多出的鸽笼数量减一。如果新的鸽笼里有两只鸽子（飞来的也算），那么多出的鸽笼数量加一。


[赛时 AC 代码](https://atcoder.jp/contests/abc391/submissions/62276731)


AC 代码（含注释）：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define PII pair<int,int>
using namespace std;
const int N=1e6+5;
const int INF=0x3f3f3f3f;
const double EPS=1e-6;
int n,q,x,y,t1[N],t2[N],cnt,op;
void solve(){
	cin>>n>>q;
	for(int i=1;i<=n;i++)t1[i]=i,t2[i]=1;//初始化
	while(q--){
		cin>>op;
		if(op==1){
			cin>>x>>y; 
			int old=t1[x];//找到老的鸽笼
			t2[old]--;//老的鸽笼鸽子数量-1
			if(t2[old]==1)cnt--;//原本多出1的笼子现在没有多
			t1[x]=y;//在新鸽笼
			t2[y]++;//新鸽笼的鸽子数量
			if(t2[y]==2)cnt++;//喜提新多出1的鸽笼
		}else cout<<cnt<<"\n";
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int T=1;
//	cin>>T;
	while(T--)solve();
	return 0;
}
```

---

## 作者：DoubleQLzn (赞：0)

我们可以维护每个鸽子所在的巢与巢里面鸽子的个数。当一个鸽子移动到一个鸽巢时，我们先处理个数，然后在把一个鸽子在的巢给改变。

因此，我们只需要维护个数。当鸽子移动到的鸽巢鸽子个数变为 $2$ 时，答案加 $1$；当鸽子原本的鸽巢鸽子个数变为 $1$ 时，答案减 $1$。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int a[1000005],now[1000005];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,q,p,h,s = 0;
	cin >> n >> q;
	for (int i = 1;i <= n;i++) a[i] = 1,now[i] = i;
	while (q--)
	{
		int op;
		cin >> op;
		if (op == 1)
		{
			cin >> p >> h;
			a[h]++;
			a[now[p]]--;
			if (a[h] == 2) s++;
			if (a[now[p]] == 1) s--;
			now[p] = h;
		}
		if (op == 2)
		{
			cout << s << '\n';
		}
	}
	return 0;
}
```

---

## 作者：xmy201315 (赞：0)

### 题目大意

有 $N$ 只鸽子，编号从 $1$ 到 $N$ ，有 $N$ 个鸽巢，编号从 $1$ 到 $N$ 。最初，鸽子 $i$ 在 $1\leq i\leq N$ 的巢 $i$ 中。

您会收到 $Q$ 个查询，您必须按顺序处理这些查询。查询有两种类型，每种都以下列格式之一给出：

- `1 P H` : 将鸽子 $P$ 移至鸽巢 $H$ 。
- `2` : 输出包含一只以上鸽子的鸽巢数量。

### 思路

我们可以用一个数组记录下每个鸟窝的鸟的只数，再记录下来现在每个鸟在那个窝，再记录下来每个窝中是否有一只以上的鸟（注意：在上面这些记录中，是边输入边进行记录）。接着我们看如果这只鸟转过去的那个窝的只数 $\ge 2$ 且再转过去之前这个窝没有两只鸟，这时我们就让答案加一。我们再看如果这只鸟转过去之前的那个窝如果现在只数 $\le 1$ 且这个窝原来是有两只鸟的，这时我们就让答案减一。

**AC code**：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 1000010
#define sz(s) s.size()
#define db double
#define mod 1000000007
#define P 998244353
#define ll long long
#define fi first
#define se second
#define pb push_back
#define mk make_pair
#define per(i,l,r) for(ll i=l;i>=r;i--)
#define rep(i,l,r) for(ll i=l;i<=r;i++)
#define in insert
#define y1 y142857
//pair<ll,ll> PII;
//unordered_map<int,int> f;
//vector<int>edges[N];
//set<int>c;
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x*f;
}
inline void write(int x,int w,int e){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10,w,e);
    putchar(x%10+'0');
    if(x==e){
        if(w==1)putchar(' ');
        if(w==2)putchar('\n');
    }
    return;
}
//time: O( )
//memory: ()kb
int n,q,a[N],ans=0,ne[N],b[N];
void sovel(){
	n=read(),q=read();
	rep(i,1,n)a[i]=1,b[i]=i;
	rep(_,1,q){
		int type=read();
		if(type==1){
			int p=read(),h=read();a[b[p]]--;a[h]++;
			if(a[h]>=2&&!ne[h])ne[h]=1,ans++;
			if(a[b[p]]<=1&&ne[b[p]])ne[b[p]]=0,ans--;b[p]=h;
		}else{
			write(ans,2,ans);
		}
	}	
}
int main(){
    int T=1;//数据组数
    while(T--)sovel();
}
```

---

## 作者：stripe_python (赞：0)

一个比较典的套路。对每个鸽巢维护一个 $cnt$，表示鸽巢中鸽子的数量，同时对鸽子维护它所属的巢穴。移动的时候更新答案。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

int n, q, opt, x, y, a[N], cnt[N];

void _main() {
	cin >> n >> q;
	iota(a, a + n + 1, 0);
	fill(cnt, cnt + n + 1, 1);
	int res = 0;
	while (q--) {
		cin >> opt;
		if (opt == 1) {
			cin >> x >> y;
			if (cnt[a[x]] == 2) res--;
			cnt[a[x]]--, a[x] = y, cnt[a[x]]++;
			if (cnt[a[x]] == 2) res++;
		} else {
			cout << res << '\n';
		}
	}
} signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr), cerr.tie(nullptr);
	
	int t = 1; for (/*cin >> t*/; t--; ) _main();
	return 0;
}
```

---

## 作者：201012280925LSY (赞：0)

## 题意
有 $N$ 只鸽子和 $N$ 个巢穴，在最开始时编号为 $i$ 的鸽子在编号为 $i$ 的巢穴中。接下来有 $Q$ 次操作，操作分为两种类型。每种查询以下面的格式给出：

- `1 P H`：把编号为 $P$ 的鸽子移到编号为 $H$ 的巢穴。
- `2`：输出多于一只鸽子的巢穴数量。
## 思路
根据题意模拟即可。由于 $N \le 10^6$，所以可以开一个数组，储存每只鸽子在哪个巢穴里。然后再开一个数组储存每个巢穴有几只鸽子。最后开一个变量 `ans` 表示有几个巢穴的鸽子数量多余一，即为答案。

但是因为 $Q \le 3 \times 10^5$，所以显然不可以遇到第二种操作就扫一遍。观察发现每次第一种操作只会使一个巢穴的鸽子数量减一，并使一个巢穴的鸽子数量加一。

所以在每次处理一操作时，如果鸽子 $P$ 原来所在的巢穴的数量为二，`ans` 就减一。然后判断如果巢穴 $H$ 的鸽子数量为一，`ans` 就加一。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,q,ans;
long long f[1000010];//每个巢穴的鸽子数量。
long long a[1000010];//每只鸽子在哪个巢穴。
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n;i++)f[i]=1,a[i]=i;//根据题意初始化。
	for(int i=1;i<=q;i++)
	{
		long long no,p,h;
		cin>>no;
		if(no==1)
		{
			cin>>p>>h;
			if(f[a[p]]==2)ans--;//鸽子 P 走了，巢穴就只剩一只了。
			if(f[h]==1)ans++;//鸽子 P 来了，巢穴就有两只了。
			f[a[p]]--;//鸽子 P 原来在的巢穴鸽子数量减一。
			f[h]++;//巢穴 H 的巢穴鸽子数量加一。
			a[p]=h;//鸽子 P 到了巢穴 H。
		}	
		else
		{
			if(ans)cout<<ans<<"\n";//有数量在两只及以上的巢穴。
			else cout<<"0\n";//没有答案。
		}
	}
	return 0;
 }
```

---

## 作者：SuyctidohanQ (赞：0)

### 思路分析

考虑使用 `vector` 进行模拟。

首先输入两个数 $N,Q$。接下来使用 `vector` 进行存储。

循环将所有的**初始**信息存入 `vector`。

接下来进行模拟。循环 $Q$ 次。

每一次对应一个操作，使用**前缀和**维护操作 $2$。操作 $1$ 的实现较为复杂，详见代码。

### 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
int main () {
    int N, Q;
    cin >> N >> Q;
    vector <int> vec (N + 1);
    for (int i = 1; i <= N; i ++) vec[i] = i;
    vector <int> cnt (N + 1, 0);
    for (int i = 1; i <= N; i ++) cnt[i] = 1; 
    int ans = 0; 
    for (int i = 0; i < Q; i ++) {
        int op;
        cin >> op;
        if (op == 1) {
            int P, H; cin >> P >> H;
            int cun = vec[P]; cnt[cun] --;
            if (cnt[cun] == 1) ans --;
            if (cnt[cun] == 0) cnt[cun] = 0; 
            cnt[H] ++;
            if (cnt[H] == 2) ans ++;
            vec[P] = H;
        } 
		else if (op == 2) cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：Tairitempest (赞：0)

## [ABC391C] Pigeonhole Query
我们用数组存储每只鸽子的所在位置，并维护当前超过一只鸽子的洞的数量。

每次操作一后，判断跑掉鸽子的洞是否仅有一只鸽子（这种情况下超过一只鸽子的洞会减少一个）以及多了鸽子的洞是否恰好有两只鸽子（这种情况下超过一只鸽子的洞会增加一个）。每次操作二直接输出数量即可。

时间复杂度 $O(N+Q)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll N,P[1000010],cnt[1000010],Q,p,h,op,nums;
int main(){
	cin>>N>>Q;
	for(int i=1;i<=N;i++) P[i]=i;
	for(int i=1;i<=N;i++) cnt[i]=1;
	while(Q--){
		cin>>op;
		if(op==1){
			cin>>p>>h;
			cnt[P[p]]--;
			if(cnt[P[p]]==1) nums--;
			cnt[h]++;
			if(cnt[h]==2) nums++;
			P[p]=h;
		}else cout<<nums<<endl;
	}
	return 0;
}
```

---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

数据范围太小了，直接用桶就可以玩。开两个数组，一个记录鸽子的位置，一个记录位置的鸽子数，动态更新就完了。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,o,a,b,p[1000005],t[1000005],ans;
inline void move(int p,int v){
	if(--t[::p[p]]==1) ans--;
	if(t[::p[p]=v]++==1) ans++;
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>m; t[0]=n; ans=1;
	for(int i=1;i<=n;++i) move(i,i);
	for(int i=1;i<=m;++i)
		if(cin>>o,o&1) cin>>a>>b,move(a,b);
		else cout<<ans<<endl;
	return 0; 
}
```

---

## 作者：zby0501_ (赞：0)

## 思路：
#### 当为操作 $1$ 时，

如果那只鸽子原来所在的巢有 $2$ 只鸽子，则将答案减 $1$。
然后把鸽子原来的巢的鸽子数减 $1$ 并将鸽子改到新的巢。

如果新的巢有 $1$ 只鸽子，那么把答案加 $1$，并把新的巢的鸽子数加 $1$。

#### 当为操作 $2$ 时，
输出答案即可。

## 代码：
```
#include<bits/stdc++.h>
//#define int long long
#define gcd(x,y) __gcd(x,y) 
using namespace std;
int n,q,ans,a[1000005],b[1000005];
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n;++i) a[i]=1,b[i]=i;
	while(q--){
		int op;
		cin>>op;
		if(op==1){
			int x,y;
			cin>>x>>y;
			if(a[b[x]]==2) --ans;
			--a[b[x]];
			b[x]=y;
			if(a[y]==1) ++ans;
			++a[y];
		}
		else{
			cout<<ans<<'\n';
			/*
			for(int i=1;i<=n;++i)
				cerr<<a[i]<<' ';
			cerr<<'\n';*/
		}
	}
	return 0;
}
```

---

## 作者：nightwatch.ryan (赞：0)

### Analysis
记第 $i$ 个鸽子在第 $pi_i$ 个巢里，第 $j$ 个巢里有 $cnt_j$ 个鸽子，记 $ans$ 为答案。

对于每个操作 $1$，首先得到第 $P$ 个鸽子当前所在巢，记第 $P$ 个鸽子当前所在巢为 $id$。然后将 $cnt_{id}$ 减去 $1$，如果 $cnt_{id}$ 等于 $1$，则 $ans$ 减去 $1$。
接下来，将第 $H$ 个巢的鸽子数加 $1$，即 $cnt_H + 1$，如果 $cnt_H$ 等于 $2$，则 $ans$ 加 $1$。最后，将 $pi_P$ 设为 $H$ 即可。

对于每个操作 $2$，输出 $ans$ 即可。
### Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

#define P(i, a, b) for(int i = a; i <= b; i++)
#define Q(i, a, b) for(int i = a; i >= b; i--)
const int maxn = 100005;
const int inf = 0x3f3f3f3f;

mt19937 rnd(chrono::duration_cast<chrono::nanoseconds>
           (chrono::system_clock::now().time_since_epoch()).count());
int randint(int L, int R) {
    uniform_int_distribution<int> dist(L, R);
    return dist(rnd);
}

map<int, int> pi;
map<int, int> cnt;
int ans;

signed main(){

    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    P(i, 1, n) pi[i] = i, cnt[i] = 1;
    while(q--){
        int op;
        cin >> op;
        if(op == 1){
            int p, h;
            cin >> p >> h;
            int P_id = pi[p];
            cnt[P_id] --;
            if(cnt[P_id] == 1){
                ans --;
            }
            cnt[h] ++;
            if(cnt[h] == 2){
                ans ++;
            }
            pi[p] = h;
        }else{
            cout << ans << endl;
        }
    }

}
```

---

## 作者：Jerry_zpl (赞：0)

本题算法：模拟。  
我们可以用一个桶数组统计每个鸽巢里鸽子的个数，然后看操作是不是查询。如果是查询，有遍历所有的鸽巢看鸽子的个数是否大于一，如果大于一，计数器加一，最后输出。如果不是查询，就将原来的鸽巢里鸽子的个数减一，再将新的鸽巢里鸽子的个数加一。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e6+5;
int tong[maxn];
int h[maxn];
int n,q;
signed main()
{
	cin>>n>>q;
	for(int i=1;i<=n;i++)
	{
		h[i]=i;
		tong[i]=1;
	}
	while(q--)
	{
		int op;
		cin>>op;
		if(op==1)
		{
			int qp;
			cin>>qp;
			int hhh;
			cin>>hhh;
			tong[h[qp]]--;
		    h[qp]=hhh;
		    tong[hhh]++;
		}
		else if(op==2)
		{
			int cnt=0;
			for(int i=1;i<=n;i++)
			{
				if(tong[i]>1)
				{
					cnt++;
				}
			}
			cout<<cnt<<"\n";
		}
	}
	return 0;
}
```
然后我们会发现，超时了，原因是我们每次都遍历了所有的鸟笼，因此我们需要改进。我们可以在操作一的时候就看如果操作前原来的鸽巢你面鸽子的个数是否等于二，如果等于二，那么 $2-1=1$，又有一个鸽巢不符合要求，计数器减一。如果操作前新鸽巢里鸽子的个数是一，那么又会有一个新的鸽巢满足要求，计数器加一。

```cpp
// LUOGU_RID: 201035955
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e6+5;
int tong[maxn];
int h[maxn];
int n,q;
signed main()
{
	cin>>n>>q;
	for(int i=1;i<=n;i++)
	{
		h[i]=i;
		tong[i]=1;
	}
	int cnt=0;
	while(q--)
	{
		int op;
		cin>>op;
		if(op==1)
		{
			int qp;
			cin>>qp;
			int hhh;
			cin>>hhh;
			if(tong[h[qp]]==2) cnt--;
			tong[h[qp]]--;
		    h[qp]=hhh;
		    if(tong[hhh]==1) cnt++;
		    tong[hhh]++;
		}
		else if(op==2)
		{
			if(cnt<0) cnt=0;
			cout<<cnt<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：cuiwl123 (赞：0)

开两个数组分别记录下每只鸽子的位置及每个鸽巢中鸽子的数量，按照题意模拟。  
很明显 $ans$ 初值为零，进行变化操作时只有第 $P_i$ 只鸽子原先在的巢 $nest[p_i]$与 将要去到的巢 $H$ 会对答案造成影响，因此更新答案时只需判断这两个巢的鸽子数量情况就可以了。  
时间复杂度 $O(n+q)$
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,num[1000006],nest[1000006],ans;
int main()
{
	cin>>n>>q;
	for(int i=1;i<=n;i++)
		num[i]=1,nest[i]=i;
	while(q--)
	{
		int opt,a,b;
		cin>>opt;
		if(opt==1)
		{
			cin>>a>>b;
			num[nest[a]]--,num[b]++;
			if(num[nest[a]]==1) ans--;
			if(num[b]==2) ans++;
			nest[a]=b;
		}
		else cout<<ans<<endl;
	}
	return 0;
}

---

## 作者：Pollococido (赞：0)

### 大致解法

招笑 2 map 解法。

开两个 map，分别记录每个巢的数量以及每个鸽子所在的巢的编号，在定义答案变量 $ans$，表示鸽子树数大于 $1$ 的巢的数量。

### 详细步骤

#### Part 1 初始化

$\forall 1 \le i \le n$。

$\operatorname{Mp}_i = i$。

$\operatorname{mp}_i = 1$。

$ans = 0$。

变量含义结合代码注释理解。

### Part 2 操作1

先考虑什么时候移动对答案有贡献。

首先是加的贡献，如果 $\operatorname{mp}_h = 1$，那么加上 $p$ 这只鸽子后，$\operatorname{mp}_h = 2$，对答案产生一次加的贡献，$ans \gets ans + 1$。

其次是减的贡献，同理，如果 $\operatorname{mp}_p = 1$，对答案产生一次减的贡献，$ans \gets ans - 1$。

### Part 3 操作 2

输出 $ans$ 即可。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, q, p, h, opt, ans;
map<int, int> Mp;//鸽子 -> 巢
map<int, int> mp;//巢 -> 数量

int main() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        Mp[i] = i;
        mp[i] = 1;
    }
    ans = 0;
    while (q--) {
        cin >> opt;
        if (opt == 1) {
            cin >> p >> h;
            int lp = mp[Mp[p]], lh = mp[h], id = Mp[p];
            mp[id]--;
            Mp[p] = h;
            mp[h]++;
            if (lh == 1) ans++;
            if (lp == 2) ans--;
        }
        else cout << ans << endl;
    }
    return 0;
}

```

---

