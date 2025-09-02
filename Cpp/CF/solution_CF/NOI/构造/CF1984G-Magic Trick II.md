# Magic Trick II

## 题目描述

奥斯卡的第一个魔术的秘密已经被揭示！因为他仍然想给 Lura 留下深刻印象，他想出了一个新点子：他仍然想要将一个排列 $p_1, p_2, \ldots, p_n$（$[1, 2, \ldots, n]$ 的一个排列）进行排序。

这一次，他选择一个整数 $k$。他希望通过多次使用以下操作，将排列按非递减顺序排序：

1. 选择一个长度为 $k$ 的连续子数组，并将其从 $p$ 中移除。
2. 将这个连续子数组插入到 $p$ 的任意位置（可以是最前面或最后面）。

为了尽可能令人印象深刻，奥斯卡希望选择最大的 $k$，使得他能够将排列排序。请帮助他找到最大的 $k$，以及一系列能够将排列排序的操作。你不需要最小化操作次数，但最多只能使用 $5n^2$ 次操作。

我们有证明，对于能够用任意次数操作排序的最大 $k$，也一定可以在不超过 $5n^2$ 次操作内完成排序。

## 说明/提示

在第一个测试用例中，只需将最后四个数字移到最前面即可。

在第二个测试用例中，可以证明 $k=4$ 或 $k=5$ 都无法完成排序。对于 $k=3$，可以先将前三个数字移到末尾，再将中间三个移到最前面，即可完成排序。

在第三个测试用例中，排列已经有序。可以选择 $k=6$，且无需任何操作。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
5
5 1 2 3 4
5
2 3 5 4 1
6
1 2 3 4 5 6```

### 输出

```
4
1
2 1
3
2
1 3
2 1
6
0```

# 题解

## 作者：honglan0301 (赞：8)

第一次场切 3200，给我开心坏了（不是）

## 分析

<0> 碰到神秘操作题先猜答案再构造，进行简单打表后你会发现惊人的结论：当 $n$ 为奇数时 $\max k\geq n-2$；当 $n$ 为偶数时 $\max k\geq n-3$。

------------

<1> 由于 $n-2$ 比 $n-3$ 更紧一些，下面我们先讨论 $n$ 为奇数的情况。

1. $k=n$：这时进行操作不会改变排列，因此当且仅当 $p_i=[1,2,\dots,n]$ 时可以取到 $k=n$。

2. $k=n-1$：这时只有两种有效操作，其效果分别为对排列进行向前/向后的循环移位，因此当且仅当 $p_i$ 是 $[1,2,\dots,n]$ 的循环移位时可以取到 $k=n-1$。此时构造也是平凡的。

3. $k=n-2$：这是问题的关键部分，此时有六种不同操作，我们关注以下两种操作的实际意义：

	操作 A： $(3,1)$：使排列向前循环移位两个单位。由于 $2 \perp n$，我们可以通过重复进行此操作达到任意循环移位的效果。
    
   操作 B： $(2,3)$：使 $[p_2,p_3,\dots,p_n]$ 向后循环移位。
   
	有了以上观察，我们尝试按照 $[1],[1,2],[1,2,3],\dots,[1,2,\dots n]$ 的顺序依次复原整个排列：
    
   当 $\forall i\leq i_0,p_i=i$ 时，我们先通过操作 A 使得 $p_1=i_0+1$；此时 $1\sim i_0$ 仍然是序列中连续的一段，因此再通过操作 B 可以让 $[p_{n-i_0+1},p_{n-i_0+2},\dots,p_n]=[1,2,\dots,i_0]$；最后再进行若干次操作 A 即可使得 $\forall i\leq i_0+1,p_i=i$。
   
   重复以上过程可以让 $i_0$ 不断增大，那么我们就解决了 $n\equiv 1\pmod 2$ 的部分。

------------
   
<2> 接下来考虑 $n \equiv 0\pmod 2$ 时有什么问题。

1. $k=n,k=n-1$：显然以上分析依然成立。

2. $k=n-2$：我们同样如上地定义操作 A/B，这时你会发现问题在于操作 A 变弱了。由于 $2\mid n$，重复进行操作 A 只能进行偶数次循环移位，那么在 $i_0\gets i_0+1$ 时不总能使得 $p_1=i_0+1$。

	考虑进行修复，注意到当无法循环移位使得 $p_1=i_0+1$ 时，一定可以使得 $p_n=i_0+1$——而这与前者是完全对称的，因此我们依然可以按照以上思路复原排列。
    
   虽然但是此时出现了例外，在 $i_0=n-1$ 时我们只能听天由命，如果排列是 $[1,2,\dots,n]$ 就成功了，否则是 $[n,1,2,\dots,n-1]$ 就死了。你会想这是为什么呢，然后发现因为每次操作都不改变逆序对个数的奇偶性，我们只能还原初始逆序对个数为偶数的排列。
   
3. $k=n-3$：

	来到最后一种情况。注意到我们先通过一些操作把 $n$ 移到序列末尾（这是容易的），然后复原 $[p_1,p_2,\dots,p_{n-1}]$ 就变成了 $n'=n-1,k'=k=n'-2$ 的问题，采用 $n'$ 为奇数的做法就好了。
    
综上所述做完了。
    
## 代码

赛时代码过于混乱冗长，不在此放出，可见 [提交记录](https://codeforces.com/contest/1984/submission/264958614)。

---

## 作者：Larryyu (赞：3)

## _前记_

第一篇黑题题解。难调。好写。~~码量不大~~。

## _Description_

给定一个大小为 $n$ 的排列 $p$，选择一个 $k$，对 $p$ 执行操作若干次使得 $p_i=i$。

每次操作有两个参数 $i,j$ 表示将从 $p_i$ 开始的连续 $k$ 个数从 $p$ 中取出，再插入此时 $p$ 中第 $j-1$ 和第 $j$ 个数之间。

如，$p=[1,2,3,4,5]$，$k$ 取 $3$，依次执行操作 $(2,1)$、$(3,2)$：

将 $[2,3,4]$ 取出，此时 $p=[1,5]$，在将 $[2,3,4]$ 放在第 $0$ 个数和第 $1$ 个数之间（即开头），操作完成后 $p=[2,3,4,1,5]$。

再执行 $(3,2)$，$p=[2,4,1,5,3]$。

## _Solution_

结论：$k\ge n-3$。

可通过打表~~瞎猜~~得出。

实际上不一定要得出这个结论，因为题目要求最大化 $k$，所以 $k$ 从 $n$ 依次递减，越早能构造出越好。

下面证明并构造。

### $k=n$ 时

此时序列无论如何操作都不会变，所以要求 $p$ 一开始就符合条件。

### $k=n-1$ 时

此时序列每次操作等于循环移一位，要求 $p$ 一开始在循环移若干位后能满足条件。

### $k=n-2$ 时

先考虑 $n$ 为奇数的情况。

每一次执行 $(3,1)$ 相当于循环移 $2$ 位，由于 $n$ 为奇数，每个数所在下标奇偶性会改变，所以在执行 $n$ 此操作以内能使序列循环移位任意长度。

1. 先把 $now$（初始为 $2$）移到第 $1$ 位，操作为 $(3,1)$

2. 在后 $n-1$ 个数中不断移位使 $now-1$ 在第 $n$ 位，操作为 $(3,2)$。

3. 循环移一次，使得 $now$ 接在 $now-1$ 的后面，操作为 $(3,1)$。

这样 $now$ 和 $now-1$ 就有序了，并且之后不会再分开。

然后 $now=now+1$，重复以上步骤直至 $now=n+1$ 时停止。

再考虑 $n$ 为偶数的情况。

每一次执行 $(3,1)$ 也相当于循环移 $2$ 位，但无法改变下标奇偶性，所以在上面操作 $1$ 中，$now$ 可能无法移到第 $1$ 位，但一定能移到第 $1$ 或 $n$ 位，因为 $1$ 和 $n$ 奇偶性不同。

如果能移到第 $1$ 位，就同上操作，否则移到第 $n$ 位，再在前 $n-1$ 个数中循环移位直到第 $n-1$ 位为 $now-1$，操作为 $(2,1)$，注意此时不再需要操作 $3$。

考虑 $1$ 到 $n-2$ 已排好序，此时有六种情况：

- $n,n-1,1\dots n-2$

- $n-1,n,1\dots n-2$
- $n,1\dots n-2,n-1$
- $n-1,1\dots n-2,n$
- $1\dots n-2,n,n-1$
- $1\dots n-2,n-1,n$

第 $2$ 种能移位成第 $5$ 种，第 $4$ 种通过操作 $(2,1)$ 变为第 $5$ 种。

另外 $3$ 种无论如何都无法变为第 $5$ 种。

为什么？

对于操作 $(i,j)$，若 $[p_i,p_{i+1},p_{i+k-1}]$ 会与 $[p_x\dots p_y]$ 相对位置发生变化，设原来有 $a$ 对逆序对，操作后则会有 $k\times(y-x+1)-a$ 对逆序对，发现逆序对数奇偶性不变，因为 $k$ 为偶数，$k\times(y-x+1)$ 也就变为偶数。

因此每次操作无法改变序列内逆序对个数。

若初始时 $p$ 就有奇数个逆序对，则最终总会有 $1$ 个逆序对不会被消去。

那么此时 $k=n-3$ 才能解决问题。

### $k=n-3$ 时

先将 $n$ 移到第 $n$ 位。

这里的操作较特殊。

设 $x$ 表示 $n$ 所在下标。

若 $x\ge k$，则将以 $n$ 为结尾的长度为 $k$ 的段放在末尾即可，操作为 $(x-(n-3)+1,4)$。

若 $x<k$，则将以 $1$ 为开头的长度为 $k$ 的段放在末尾，操作为 $(1,4)$，即循环移位 $3$ 位，直到满足上面的条件并执行上面的操作。

然后使 $1\dots n-1$ 在前 $n-1$ 位排序，可以发现，此时总长 $n-1$ 为奇数，且 $k=n-3=(n-1)-2$，所以将其视为上面 $n$ 为奇数的情况并做操作即可。

注意下面实现时，每次操作暴力改变是 $O(n)$ 的，但实际上可以用 $O(1)$ 的链表或其他东西维护，使其总时间复杂度降为 $O(n^2)$，但由于 $n^2$ 次操作严格跑不满，所以 $O(n^3)$ 也能过。

## _Code_

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n,k,cnt,now;
int a[1010],b[1010];
int ans[5000500][2];
void alter(int x,int y){
	int s=1;
	ans[++cnt][0]=x,ans[cnt][1]=y;
	for(int i=1;i<y;i++){
		if(s>=x&&s<=x+k) s=x+k;
		b[i]=a[s++];
	}
	for(int i=y;i<=y+k-1;i++){
		b[i]=a[x+i-y];
	}
	for(int i=y+k;i<=n;i++){
		if(s>=x&&s<=x+k) s=x+k;
		b[i]=a[s++];
	}
	for(int i=1;i<=n;i++){
		a[i]=b[i];
	}
}
int find(int x){
	for(int i=1;i<=n;i++){
		if(a[i]==x) return i;
	}
}
void print(){
	cout<<cnt<<'\n';
	for(int i=1;i<=cnt;i++){
		cout<<ans[i][0]<<" "<<ans[i][1]<<'\n';
	}
}
void solve(){
	cin>>n;
	cnt=0;
	int cnt1=0,cnt2=0;
	cin>>a[1];
	for(int i=2;i<=n;i++){
		cin>>a[i];
		if(a[i]!=a[i-1]+1) cnt2++;
		for(int j=1;j<i;j++){
			if(a[i]<a[j]) cnt1++;
		}
	}
	if(cnt2==0){
		cout<<n<<'\n'<<0<<'\n';
		return ;
	}
	if(cnt2==1){
		k=n-1;
		cout<<k<<'\n';
		while(a[1]!=1){
			alter(2,1);
		}
		print();
		return ;
	}
	if(n%2==1){
		k=n-2,now=2;
		cout<<k<<'\n';
		while(now<=n){
			while(a[1]!=now){
				alter(3,1);
			}
			while(a[n]!=now-1){
				alter(3,2);
			}
			alter(3,1);
			now++;
		}
		while(a[1]!=1){
			alter(3,1);
		}
		print();
		return ;
	}
	if(cnt1%2==0){
		k=n-2,now=2;
		cout<<k<<'\n';
		int type;
		while(now<=n){
			type=find(now)%2;
			if(type==0){
				while(a[n]!=now){
					alter(3,1);
				}
				while(a[n-1]!=now-1){
					alter(2,1);
				}
				now++;
			}else{
				while(a[1]!=now){
					alter(3,1); 
				}
				while(a[n]!=now-1){
					alter(3,2);
				}
				alter(3,1);
				now++;
			}
		}
		while(a[1]!=1){
			alter(3,1);
		}
		print();
		return ;
	}else{
		k=n-3,now=2;
		cout<<k<<'\n';
		while(a[n]!=n){
			int x=find(n);
			if(x<n-3){
				alter(1,4);
			}else{
				alter(x-(n-3)+1,4);
			}
		}
		while(now<=n-1){
			while(a[1]!=now){
				alter(3,1);
			}
			while(a[n-1]!=now-1){
				alter(3,2);
			}
			while(a[1]!=1){
				alter(3,1);
			}
			now++;
		}
		print();
		return ;
	}
	
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：wxzzzz (赞：2)

### 思路

对于 $a$ 已经排序，$k=n$，无需操作；对于 $a$ 是排序数组的循环移位，$k=n-1$，可通过操作 $(1,2)$ 将数组向右循环移位。

接下来考虑 $k=n-2$ 可用于哪些情况。

考虑 $k=n-2$ 不可用于哪些情况。

若 $n$ 是偶数，且 $a$ 中逆序对数是奇数，那么 $n-2$ 是偶数，移动 $n-2$ 个数能增减的逆序对数也是偶数，最终逆序对数永远是奇数，无法达到排序后逆序对为 $0$ 的状态。

考虑对与其他情况构造一组 $k=n-2$ 的合法解。

假设当前 $[n-i+2,n]$ 的数分别为 $1\sim i-1$。将 $i$ 循环移位移至末尾（此操作不会改变 $1\sim i-1$ 之间的顺序），循环移位将 $1\sim i-1$ 移至 $[n-i+1,n-1]$。

但这样有个问题，$k=n-2$ 只能将长度位 $n-1$ 的序列循环移位，如果 $i$ 当前处在序列开头就不能直接移。

考虑进行一次操作 $(3,1)$，就使 $i$ 移到了 $[2,n]$，然后对 $[2,n]$ 循环位移直至 $i$ 到达末尾即可。

但又有了一个问题。举个例子，令 $a=\{4,5,1,2,3\}$ 当前 $i=4$，上述方法会先将 $4$ 移至 $[2,n]$，再将 $4$ 移至末尾。

$$4,5,[1,2,3]$$

$$\Darr$$

$$[1,2,3],4,5$$

$$1,[2,3,4],5$$

$$\Darr$$

$$1,5,[2,3,4]$$

发现 $1\sim 3$ 的顺序被打乱了。

又发现这种情况对于 $i$ 并不普遍。例如 $i=3$：

$$3,4,[5,1,2]$$

$$\Darr$$

$$[5,1,2],3,4$$

$$5,[1,2,3],4$$

$$\Darr$$

$$5,4,[1,2,3]$$

$1\sim 2$ 的顺序未被打乱。

注意到只有 $[3,n]$ 恰好为 $1\sim i-1$ 时才有上述问题，而该情况仅限于 $i=n-1$。

$i=n-1$ 时若 $i$ 在开头，那么 $1\sim i-1$ 在 $[n-i+2,n]$ 上排好序，$n$ 在位置 $2$，一次操作 $(3,1)$ 便可完成排序。

特判上述情况即可。

现在假设已经按顺序完成 $i=1\sim n-1$ 的操作，序列将变成形如：

$$n,1,2,3,\dots,n-1$$

考虑将 $n$ 移至末尾。

发现一次操作 $(3,1)$ 相当于使序列进行两次向左循环移位，那么 $\cfrac{n+1}{2}$ 次 $(3,1)$ 操作相当于将序列向左循环移位 $n+1$ 位，相当于移动一位。

按上述操作即可将 $n$ 从开头移至末尾。

现在考虑 $n$ 为偶数且逆序对为奇数的情况。

构造一组 $k=n-3$ 的可行解。

可先将 $n$ 移至序列末尾（同理，如果在开头两位就先往后移两次），令 $n\gets n-1$，做一遍 $k=n-2$ 的解即可。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int T, n, m, a[1005], t[1005], tt[1005], ans[5000005][2];
bool check() {
    for (int i = 1; i <= n; i++)
        if (t[i] != i)
            return 0;
    return 1;
}
void add(int x, int y) {
    ans[++m][0] = x;
    ans[m][1] = y;
}
bool solve1() {
    m = 0;
    for (int i = 1; i <= n; i++)
        t[i] = a[i];
    return check();
}
void mv(int x, int y, int k) {  //题意操作
    if (x == y)
        return;
    int now = 0;
    if (x < y) {
        y += k;
        for (int i = 1; i < x; i++)
            tt[++now] = t[i];
        for (int i = x + k; i < y; i++)
            tt[++now] = t[i];
        for (int i = x; i <= x + k - 1; i++)
            tt[++now] = t[i];
        for (int i = y; i <= n; i++)
            tt[++now] = t[i];
    } else {
        for (int i = 1; i < y; i++)
            tt[++now] = t[i];
        for (int i = x; i <= x + k - 1; i++)
            tt[++now] = t[i];
        for (int i = y; i < x; i++)
            tt[++now] = t[i];
        for (int i = x + k; i <= n; i++)
            tt[++now] = t[i];
    }
    for (int i = 1; i <= n; i++)
        t[i] = tt[i];
}
void rep(int l, int r, int k) {  //将 [l, r] 循环移位 k 位
    int now = l - 1;
    for (int i = r - k + 1; i <= r; i++)
        tt[++now] = t[i];
    for (int i = l; i <= r - k; i++)
        tt[++now] = t[i];
    for (int i = l; i <= r; i++)
        t[i] = tt[i];
}
bool solve2() {  //k = n - 1
    m = 0;
    for (int i = 1; i <= n; i++)
        t[i] = a[i];
    for (int i = 1; i <= n; i++) {
        if (check())
            return 1;
        mv(2, 1, n - 1);
        add(2, 1);
    }
    return 0;
}
bool solve3(bool op) {  //k = n - 2
    if (!op)
        m = 0;
    if (!(n & 1)) {
        int cnt = 0;
        for (int i = 1; i < n; i++)
            for (int j = i + 1; j <= n; j++)
                if (a[i] > a[j])
                    cnt++;
        if (cnt & 1)
            return 0;
    }
    if (n == t[1]) {
        mv(2, 1, n - 2);
        add(2, 1);
    }
    int pos = 1;
    while (t[pos] != n)
        pos++;
    rep(2, n, n - pos);
    for (int i = 1; i <= n - pos; i++)
        add(2, 3);
    for (int i = 2, pos; i < n; i++) {
        //将 i 移至末尾
        if (i == t[1]) {
            mv(3, 1, n - 2);
            add(3, 1);
            if (i == n - 1)
                return check();
        }
        pos = 1;
        while (t[pos] != i)
            pos++;
        rep(2, n, n - pos);
        for (int j = 1; j <= n - pos; j++)
            add(2, 3);
        //将 1,2,...,i-1 接在 i 前面
        pos = 1;
        while (t[pos] != i - 1)
            pos++;
        rep(1, n - 1, n - 1 - pos);
        for (int j = 1; j <= n - 1 - pos; j++)
            add(1, 2);
    }
    rep(1, n, n - 1);
    for (int i = 1; i <= (n + 1) / 2; i++)
        add(3, 1);
    //将 n 从开头移至末尾
    return check();
}
void solve4() {  //k = n - 3
    m = 0;
    //将 n 移至末尾
    if (n == t[1]) {
        mv(2, 1, n - 3);
        add(2, 1);
    }
    if (n == t[2]) {
        mv(3, 2, n - 3);
        add(3, 2);
    }
    int pos = 1;
    while (t[pos] != n)
        pos++;
    rep(3, n, n - pos);
    for (int i = 1; i <= n - pos; i++)
        add(3, 4);
    n--;
    solve3(1);
    n++;
}
int main() {
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        if (solve1())
            cout << n << '\n';
        else if (solve2())
            cout << n - 1 << '\n';
        else if (solve3(0))
            cout << n - 2 << '\n';
        else {
            solve4();
            cout << n - 3 << '\n';
        }
        cout << m << '\n';
        for (int i = 1; i <= m; i++)
            cout << ans[i][0] << ' ' << ans[i][1] << '\n';
    }
    return 0;
}
```

---

## 作者：Ihave4oranges (赞：2)

赛时 F 和 G 都没有调出来，写篇题解纪念一下。

首先判掉 $k=n$ 和 $k=n-1$ 的情况，剩下的答案只能是 $k=n-2$ 或 $k=n-3$，接下来的构造即证明。

注意到如果 $n$ 是偶数，$n-2$ 也是偶数，那么每次操作不会改变逆序对的奇偶性，所以 $k$ 有可能要取 $n-3$。在这样的情况下，我们可以先把排列中的 $n$ 放到 $n$ 号位置，然后再做 $n$ 是奇数的。下面给出 $k=n-2$ 的构造方法。

注意到构造的方案当中只能出现 `1 2`，`2 1`，`2 3`，`3 2`，`1 3`，`3 1`，并且 `1 3` 等价于 `1 2\n2 3`，`3 1` 类似，所以可以在忽略操作次数限制的前提下只使用前四种操作。下面设 `A` 表示 `1 2`，`B` 表示 `2 3`，`A'` 表示 `2 1`，`B'` 表示 `3 2`。

先把 $1\sim n-2$ 按顺序放在 $2\sim n-1$ 的位置。每次把 $i+1$ 放到 $1\sim i$ 之后，这个可以先把 $i+1$ 移动到 $n$ 号位置，然后用若干次 `A` 把 $1\sim i$ 移到 $n-i\sim n-1$，最后再做一次 `B'`。

如果这些结束之后，一号位恰好是 $n-1$，那么只需要再做一个 `A'`。否则根据开头的讨论，这里 $n$ 一定是奇数。

同样先做一个 `2 1`，这样接下来的任务就是交换 $n-1$ 和 $n$。把这个看作是让 $n$ 在 $2\sim n$ 的环上向后跳过 $n-1$，那么这也等价于向前依次跳过 $n-2,n-3,\dots,2$（此时 $1$ 已经归位）。因为 $n$ 是奇数，所以 $2\sim n-2$ 一共有偶数个。考虑每次把 $n$ 向前跳两个位置。注意到 `BA'` 可以使 $1,n-1,n$ 这三个位置进行循环移动，相当于是先交换 $1$ 和 $n$，再交换 $n$ 和 $n-1$。我们可以通过 `AB` 把 位置 $n-1,n-3,n-2$ 的数移动到 $1,n-1,n$，所以把位置 $n-1$ 移动到 $n-3$ 可以用 `ABBA'B'A'` 完成。最后用 `BB` 把位置 $n-3$（现在这里的数应该是 $n$）再移到位置 $n-1$，就可以递推地做了。**总结一下就是进行 $\frac{n-3}{2}$ 次 `ABBA'B'A'BB`，之后再 `B` 就完成了。**

>由于有些同学喜欢直接抄代码，我决定将代码放在下面，方便张老师抓住这些抄题解的同学。——sszcdjr

```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,a[1005],b[1005];
vector<pair<int,int> > ans;
void Print(){
	printf("%d\n",ans.size());
	for(auto p:ans) printf("%d %d\n",p.first,p.second);
}
void Move(int l,int r,int x){
	if(x<0) x+=r-l+1;
	for(int i=l;i<=r;++i) b[(i+x-l)%(r-l+1)+l]=a[i];
	for(int i=l;i<=r;++i) a[i]=b[i];
}
signed main(){
	scanf("%d",&t);
	while(t--){
		ans.clear();
		scanf("%d",&n);
		for(int i=1;i<=n;++i) cin>>a[i];
		bool flag=1;
		for(int i=1;i<=n;++i)
			if(a[i]!=i) flag=0;
		if(flag){
			printf("%d\n0\n",n);
			continue;
		}
		flag=1;
		for(int i=1;i<n;++i)
			if(a[i+1]-a[i]==1||a[i+1]-a[i]==1-n);
			else flag=0;
		if(flag){
			printf("%d\n",n-1);
			int p;
			for(int i=1;i<=n;++i)
				if(a[i]==1) p=i;
			printf("%d\n",p-1);
			for(int i=1;i<p;++i) printf("2 1\n");
			continue;
		}
		int inv=0;
		for(int i=1;i<n;++i)
			for(int j=i+1;j<=n;++j)
				if(a[i]>a[j]) ++inv;
		if((inv&1)&&((n-1)&1)){
			printf("%d\n",n-3);
			int posn;
			for(int i=1;i<=n;++i)
				if(a[i]==n) posn=i;
			if(posn==1){
				ans.push_back({2,1});
				Move(1,n-2,-1);
				posn=n-2;
			}else if(posn==2){
				ans.push_back({1,2});
				Move(1,n-2,1);
				posn=3;
			}
			for(int i=posn;i<n;++i) ans.push_back({3,4});
			Move(3,n,n-posn);
			--n;
			if(a[1]==1){
				ans.push_back({1,2});
				int tmp=a[n-1];
				for(int i=n-1;i>=2;--i) a[i]=a[i-1];
				a[1]=tmp;
			}else if(a[n]==1){
				ans.push_back({2,3});
				for(int i=n;i>=3;--i) a[i]=a[i-1];
				a[2]=1;
			}
			for(int i=2;i<=n-2;++i){
				int pos1,posi;
				for(int j=1;j<=n;++j)
					if(a[j]==1) pos1=j;
				for(int j=1;j<=n;++j)
					if(a[j]==i) posi=j;
				if(posi==1){
					if(pos1==2){
						ans.push_back({1,2});
						int tmp=a[n-1];
						for(int j=n-1;j>=2;--j) a[j]=a[j-1];
						a[1]=tmp;
						++pos1;++posi;
					}else{
						ans.push_back({2,1});
						for(int j=1;j<=n-2;++j) a[j]=a[j+1];
						a[n-1]=i;
						--pos1;
						posi=n-1;
					}
				}
				if(posi!=n){
					if(posi<pos1){
						for(int j=2;j<=posi;++j) ans.push_back({3,2});
						Move(2,n,-(posi-1));
						pos1-=posi-1;
						posi=n;
					}else{
						for(int j=posi;j<n;++j) ans.push_back({2,3});
						Move(2,n,n-posi);
						pos1+=n-posi;
						posi=n;
					}
				}
				for(int j=pos1+i-2;j<n-1;++j) ans.push_back({1,2});
				Move(1,n-1,n-1-(pos1+i-2));
				pos1+=n-1-(pos1+i-2);
				ans.push_back({3,2});
				Move(2,n,-1);
			}
			ans.push_back({2,1});
			Move(1,n-1,-1);
			if(a[n-1]==n-1){
				Print();
				continue;
			}else{
				for(int i=1;i<=(n-3)/2;++i){
					ans.push_back({1,2});
					ans.push_back({2,3});
					ans.push_back({2,3});
					ans.push_back({2,1});
					ans.push_back({3,2});
					ans.push_back({2,1});
					ans.push_back({2,3});
					ans.push_back({2,3});
				}
				ans.push_back({2,3});
				Print();
			}
		}else{
			printf("%d\n",n-2);
			if(a[1]==1){
				ans.push_back({1,2});
				int tmp=a[n-1];
				for(int i=n-1;i>=2;--i) a[i]=a[i-1];
				a[1]=tmp;
			}else if(a[n]==1){
				ans.push_back({2,3});
				for(int i=n;i>=3;--i) a[i]=a[i-1];
				a[2]=1;
			}
			for(int i=2;i<=n-2;++i){
				int pos1,posi;
				for(int j=1;j<=n;++j)
					if(a[j]==1) pos1=j;
				for(int j=1;j<=n;++j)
					if(a[j]==i) posi=j;
				if(posi==1){
					if(pos1==2){
						ans.push_back({1,2});
						int tmp=a[n-1];
						for(int j=n-1;j>=2;--j) a[j]=a[j-1];
						a[1]=tmp;
						++pos1;++posi;
					}else{
						ans.push_back({2,1});
						for(int j=1;j<=n-2;++j) a[j]=a[j+1];
						a[n-1]=i;
						--pos1;
						posi=n-1;
					}
				}
				if(posi!=n){
					if(posi<pos1){
						for(int j=2;j<=posi;++j) ans.push_back({3,2});
						Move(2,n,-(posi-1));
						pos1-=posi-1;
						posi=n;
					}else{
						for(int j=posi;j<n;++j) ans.push_back({2,3});
						Move(2,n,n-posi);
						pos1+=n-posi;
						posi=n;
					}
				}
				for(int j=pos1+i-2;j<n-1;++j) ans.push_back({1,2});
				Move(1,n-1,n-1-(pos1+i-2));
				pos1+=n-1-(pos1+i-2);
				ans.push_back({3,2});
				Move(2,n,-1);
			}
			ans.push_back({2,1});
			Move(1,n-1,-1);
			if(a[n-1]==n-1){
				Print();
				continue;
			}else{
				for(int i=1;i<=(n-3)/2;++i){
					ans.push_back({1,2});
					ans.push_back({2,3});
					ans.push_back({2,3});
					ans.push_back({2,1});
					ans.push_back({3,2});
					ans.push_back({2,1});
					ans.push_back({2,3});
					ans.push_back({2,3});
				}
				ans.push_back({2,3});
				Print();
			}
		}
	}
	return 0;
}
```

---

## 作者：MarSer020 (赞：1)

想题一小时，写题一下午。

$\Large\text{Solution}$

Ad-hoc 题先打表找规律。对 $n=5$ 打表发现 $k_{min}=3$，对 $n=6$ 打表发现只有大约一半满足 $k\ge 4$，对 $n=7$ 打表发现 $k_{min}=5$，对 $n=8$ 打表发现只有大约一半满足 $k\ge 6$。

大胆猜测结论：当 $n\equiv1\pmod 2$ 时 $k\ge n-2$，否则 $k\ge n-3$。

考虑证明。当 $k\ge n-1$ 时的情况是显然的。

下面以 $n=5$ 为例说明当 $k=n-2$ 时对于 $n$ 为奇数情况可以交换相邻两位置的值，红色为每次操作的位置。

$$
\begin{matrix}
\color{black}a_1a_2\color{red}a_3a_4a_5\\
\color{black}a_3a_4\color{red}a_5a_1a_2\\
\color{black}a_5\color{red}a_1a_2a_3\color{black}a_4\\
\color{black}a_1a_2a_3a_5a_4
\end{matrix}
$$

注意到交换任意位置相邻两个时，可以先移到序列末尾，再复原。故结论成立。

对于 $n$ 为偶数的情况，有结论：当序列逆序对个数为偶数时 $k\ge n-2$，否则 $k\ge n-3$。证明如下：

当 $n$ 为偶数，$k=n-2$ 时有如下操作（以 $n=6$ 为例）：

$$
\begin{matrix}
\color{red}a_1a_2a_3a_4\color{black}a_5a_6\\
\color{black}a_5\color{red}a_6a_1a_2a_3\color{black}a_4\\
\color{black}a_6\color{red}a_1a_2a_3a_5\color{black}a_4\\
a_1a_2a_3a_5a_6a_4
\end{matrix}
$$

即可以使相邻 $3$ 个数循环移位。观察到总能通过这种方法还原前 $n-2$ 个数，且这种方法不改变序列逆序对的奇偶性，所以当逆序对数量为偶数时可以还原序列。

考虑当 $k=n-3$ 且 $n$ 为偶数时可以将 $n$ 移至末尾，此时转化为 $k=n-2$ 且 $n$ 为奇数的问题。所以总是有 $n$ 为偶数时 $k\ge n-3$。

综上所述，结论正确。

考虑代码实现：

$n$ 为奇数时，每次交换两个数使用次数是 $O(n)$ 的，使用冒泡排序显然不可行。考虑依次还原第 $i$ 个数：当前已经还原了 $[1,i-1]$ 中的数，如何还原第 $i$ 个数。

考虑此时可以将序列进行循环移位。故先将 $i$ 移至第一位，此时观察到 $[1,i-1]$ 在一个连续段内。对 $[2,n]$ 子序列进行循环移位使 $a_n=i-1$，再将整个序列循环移位使 $a_1=1$ 即可。

前面提到 $n$ 为偶数且 $k=n-3$ 时可以转化为 $n$ 为奇数的情况。考虑 $k=n-2$ 时：此时循环移位可能会出现无法使 $a_1=i$ 的情况。观察到此时必然可以使 $a_n=i$，再循环移位 $[1,n-1]$ 使 $a_{n-1}=i-1$，再循环移位 $[1,n]$ 使 $a_1=1$，即可还原 $[1,i]$。注意此时若无法使 $a_1=1$，由上述证明结论有 $i\in [1,n-2]$，故直接对 $[1,n-1]$ 循环移位即可。

$\Large\text{Code}$

注意代码细节。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,T,a[1005],b[1005];
vector<pair<int,int>>ans;
bool chk1(){
	for(int i=1;i<=n;i++)
		if(a[i]!=i)
			return 0;
	return 1;
}
bool chk2(){
	for(int i=2;i<=n;i++)
		if(a[i]!=(a[1]+i-2)%n+1)
			return 0;
	return 1;
}
void sol1(int val){
	int p=0;
	for(int i=1;i<=n;i++)
		if(a[i]==val){
			p=i;
			break;
		}
	memcpy(b,a,sizeof(a));
	for(int i=p;i<=n;i++)
		a[i-p+1]=b[i];
	for(int i=1;i<p;i++)
		a[i+(n-p+1)]=b[i];
	while(p!=1)
		ans.emplace_back(3,1),p=(p-3+n)%n+1;
	if(val!=1){
		for(int i=1;i<=n;i++)
			if(a[i]==val-1){
				p=i;
				break;
			}
		memcpy(b,a,sizeof(a));
		for(int i=2;i<=p;i++)
			a[i+(n-p)]=b[i];
		for(int i=p+1;i<=n;i++)
			a[i-p+1]=b[i];
		while(p!=n)
			ans.emplace_back(2,3),p++;
		for(int i=1;i<=n;i++)
			if(a[i]==1){
				p=i;
				break;
			}
		memcpy(b,a,sizeof(a));
		for(int i=p;i<=n;i++)
			a[i-p+1]=b[i];
		for(int i=1;i<p;i++)
			a[i+(n-p+1)]=b[i];
		while(p!=1)
			ans.emplace_back(3,1),p=(p-3+n)%n+1;
	}
}
void sol2(){
	int p=0;
	for(int i=1;i<=n;i++)
		if(a[i]==n){
			p=i;
			break;
		}
	if(p!=n){
		int tmp=0;
		while(p<=n-3)
			ans.emplace_back(1,4),p+=3,tmp+=3;
		memcpy(b,a,sizeof(a));
		for(int i=n-tmp+1;i<=n;i++)
			a[i+tmp-n]=b[i];
		for(int i=1;i<=n-tmp;i++)
			a[i+tmp]=b[i];
		if(p!=n){
			ans.emplace_back(p-n+4,4),memcpy(b,a,sizeof(a));
			for(int i=p-n+4;i<=p;i++)
				a[i+(n-p)]=b[i];
			for(int i=p+1;i<=n;i++)
				a[i-(n-3)]=b[i];
		}
	}
	n--;
	for(int i=1;i<=n;i++)
		if(a[i]!=i)
			sol1(i);
}
void sol3(int val){
	int p=0;
	for(int i=1;i<=n;i++)
		if(a[i]==val){
			p=i;
			break;
		}
	if(val!=1){
		if(p&1){
			memcpy(b,a,sizeof(a));
			for(int i=p;i<=n;i++)
				a[i-p+1]=b[i];
			for(int i=1;i<p;i++)
				a[i+(n-p+1)]=b[i];
			while(p!=1)
				ans.emplace_back(3,1),p-=2;
			for(int i=1;i<=n;i++)
				if(a[i]==val-1){
					p=i;
					break;
				}
			memcpy(b,a,sizeof(a));
			for(int i=p+1;i<=n;i++)
				a[i-p+1]=b[i];
			for(int i=2;i<=p;i++)
				a[i+(n-p)]=b[i];
			while(p!=n)
				ans.emplace_back(2,3),p++;
			ans.emplace_back(3,1),memcpy(b,a,sizeof(a)),a[n-1]=b[1],a[n]=b[2];
			for(int i=3;i<=n;i++)
				a[i-2]=b[i];
		}
		else{
			memcpy(b,a,sizeof(a));
			for(int i=1;i<=p;i++)
				a[i+(n-p)]=b[i];
			for(int i=p+1;i<=n;i++)
				a[i-p]=b[i];
			while(p!=n)
				ans.emplace_back(1,3),p+=2;
			for(int i=1;i<=n;i++)
				if(a[i]==val-1){
					p=i;
					break;
				}
			memcpy(b,a,sizeof(a));
			for(int i=1;i<=p;i++)
				a[i+(n-p-1)]=b[i];
			for(int i=p+1;i<n;i++)
				a[i-p]=b[i];
			while(p!=n-1)
				ans.emplace_back(1,2),p++;
		}
	}
	for(int i=1;i<=n;i++)
		if(a[i]==1){
			p=i;
			break;
		}
	if(!(p&1))
		p--;
	memcpy(b,a,sizeof(a));
	for(int i=p;i<=n;i++)
		a[i-p+1]=b[i];
	for(int i=1;i<p;i++)
		a[i+(n-p+1)]=b[i];
	while(p>2)
		ans.emplace_back(3,1),p-=2;
	if(a[1]!=1){
		ans.emplace_back(2,1),memcpy(b,a,sizeof(a)),a[n-1]=b[1];
		for(int i=2;i<n;i++)
			a[i-1]=b[i];
	}
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0),cin>>T;
	while(T--){
		cin>>n,ans.clear();
		for(int i=1;i<=n;i++)
			cin>>a[i];
		if(chk1())
			cout<<n<<"\n";
		else if(chk2()){
			cout<<n-1<<'\n';
			for(int i=1;i<=a[1]-1;i++)
				ans.emplace_back(1,2);
		}
		else if(n&1){
			cout<<n-2<<'\n';
			for(int i=1;i<=n;i++)
				if(a[i]!=i)
					sol1(i);
		}
		else{
			bool f=0;
			for(int i=1;i<=n;i++)
				for(int j=i+1;j<=n;j++)
					if(a[i]>a[j])
						f^=1;
			if(f)
				cout<<n-3<<'\n',sol2();
			else{
				cout<<n-2<<'\n';
				for(int i=1;i<=n;i++)
					if(a[i]!=i)
						sol3(i);
			}
		}
		cout<<ans.size()<<'\n';
		for(auto x:ans)
			cout<<x.first<<' '<<x.second<<'\n';
	}
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/CF1984G)

**题目大意**

> 给定 $1\sim n$ 排列 $p$，选定 $k$，每次操作可以把 $p$ 的一个长度为 $k$ 的子段移动到任意位置，求最大的 $k$ 使得可以通过这个操作给 $p$ 排序，构造方案。
>
> 数据范围：$n\le 10^3$。

**思路分析**

我们发现 $k$ 相当大，大部分时候 $k\in \{n-2,n-3\}$，特判掉 $k\ge n-1$ 的情况。

我们考虑 $k=n-2$ 时能进行什么操作：

- 显然能任意循环移位 $a[1,n-1],a[2,n]$。
- 如果 $n$ 是奇数，那么可以任意循环移位 $a[1,n]$。

因此当 $n$ 是奇数的时候一定可以还原：

从小到大枚举 $i$，每次操作把 $i$ 放到 $1\sim i-1$ 后面，使他们连续。

构造很简单，先循环移位整个排列，把 $i$ 放在 $a_1$，然后循环移位 $a[2,n]$，把 $1\sim i-1$ 放到 $a[n-i+2,n]$  上即可。

如果 $n$ 是偶数，那我们不一定能任意循环移位 $a[1,n]$，只能移位偶数步。

但此时我们依然能将 $i$ 放在 $a_1/a_n$，如果 $a_n=i$，就循环移位 $a[1,n-1]$ 把 $1\sim i-1$ 放到 $a[n-i+1,n-1]$ 即可。

但这样操作结束的时候可能会得到 $a=[n,1,2,\dots,n-1]$，此时 $k$ 为偶数，容易发现任意操作不能改变逆序对的奇偶性，所以得到这个排列后在 $k=n-2$ 时是无解的。

那么我们不得不取 $k=n-3$，做法就是把 $n$ 放到 $a_n$ 上，然后在 $a[1,n-1]$ 里做 $k=n-2$ 的构造。

时间复杂度 $\mathcal O(n^3)$。

**代码呈现**

```cpp
#include<bits/stdc++.h> 
using namespace std;
vector <array<int,2>> wys;
const int MAXN=1005;
int n,a[MAXN],z;
bool spj() {
	for(int i=2;i<=n;++i) if(a[i]!=a[i-1]%n+1) return false;
	if(a[1]==1) z=n;
	else {
		z=n-1;
		for(int i=1;a[i]!=1;++i) wys.push_back({2,1});
	}
	return true;
}
void rot() { wys.push_back({3,1}),rotate(a+1,a+3,a+n+1); }
void rotL() { wys.push_back({2,1}),rotate(a+1,a+2,a+n); }
void rotR() { wys.push_back({3,2}),rotate(a+2,a+3,a+n+1); }
void build() {
	z=n-2;
	for(int i=1;i<=n;++i) {
		while(a[1]!=i) rot();
		if(i>1) while(a[n]!=i-1) rotR();
	}
	while(a[1]!=1) rot();
}
void solve() {
	cin>>n,wys.clear();
	for(int i=1;i<=n;++i) cin>>a[i];
	if(spj()) return ;
	if(n%2==1) return build();
	int inv=0;
	for(int i=1;i<=n;++i) for(int j=i+1;j<=n;++j) if(a[i]>a[j]) ++inv;
	if(inv%2==1) {
		while(a[n]!=n) {
			int x=find(a+1,a+n+1,n)-a;
			x=min(x,3),wys.push_back({x,x+1});
			rotate(a+x,a+x+n-3,a+x+n-2);
		}
		return --n,build();
	}
	z=n-2;
	for(int i=1;i<=n;++i) {
		while(a[1]!=i&&a[n]!=i) rot();
		if(i==1) continue;
		if(a[1]==i) while(a[n]!=i-1) rotR();
		else while(a[n-1]!=i-1) rotL();
	}
	while(a[1]!=1) rot();
}
signed main() {
	ios::sync_with_stdio(false);
	int T; cin>>T;
	while(T--) {
		solve();
		cout<<z<<"\n"<<wys.size()<<"\n";
		for(auto o:wys) cout<<o[0]<<" "<<o[1]<<"\n";
	}
	return 0;
}
```

---

## 作者：bluewindde (赞：0)

发现样例的 $k$ 值都比较大，考虑不同 $k$ 值的含义。因为本题操作次数限制很松弛，所以可以暂时抛开操作次数的限制。

$k = n$ 时，操作不会改变排列。如果排列 $p$ 已然有序，则 $k = n$ 最优。

$k = n - 1$ 时，操作相当于将排列循环移位。如果排列 $p$ 可以通过循环移位达到有序状态，则 $k = n - 1$ 最优，此时至多操作 $n$ 次。

$k = n - 2$ 时，考虑以下几个操作：

- 操作 $[3, 1]$ 会将排列从 $p_1, p_2, p_3, \cdots p_n$ 变为 $p_3, p_4, p_5, \cdots p_n, p_1, p_2$，即向左循环移位两轮。
- 操作 $[2, 3]$ 会将排列从 $p_1, p_2, p_3, \cdots p_n$ 变为 $p_1, p_n, p_2, p_3, p_4, \cdots p_{n - 1}$，即对后 $n - 1$ 个位置向左循环移位。

要将前 $t$ 个数有序的排列 $1, 2, 3, \cdots t, \cdots$ 扩展到前 $t + 1$ 个数有序的排列 $1, 2, 3, \cdots t, t + 1, \cdots$。

如果 $n$ 为奇数，进行若干次操作 $[3, 1]$ 后一定可以得到原排列的所有循环移位。此时，可以先通过若干次操作 $[3, 1]$ 将 $t + 1$ 移动到第一个位置，并通过若干次操作 $[2, 3]$ 将 $1, 2, 3, \cdots t$ 移动到末尾，这样在下一次操作 $[3, 1]$ 时就可以得到一段 $1, 2, 3, \cdots t, t + 1$，完成扩展。可以说明，操作次数至多为 $3n^2$ 次。

如果 $n$ 为偶数，操作 $[3, 1]$ 不再得到原排列的所有循环移位。如果通过逆序对描述排列的有序程度，操作 $[3, 1]$ 这时不能改变逆序对数的奇偶性，所以如果原排列有奇数个逆序对，最好情况下会得到 $1, 2, 3, \cdots n - 2, n, n - 1$，不可能进一步消去逆序对，需要分开讨论。反之，当原排列逆序对数为偶数时，虽然 $t + 1$ 不一定能被恰好移动到第一个位置，但如果其不能被移动到第一个位置，则一定能被移动到最后一个位置。（因为奇偶性）移动到最后一个位置时同理处理亦可。可以说明，操作次数至多为 $2n^2$ 次。

继续讨论 $n$ 为偶数且原排列有偶数个逆序对的情况，此时可以通过一些操作将 $n$ 移动到排列末尾。然后就不用再考虑这个数，转化为 $n$ 为奇数的情况求解。可以说明，操作次数至多为 $3n^2 + n$ 次。

需要注意，如果直接模拟上述过程，时间复杂度会达到 $O(n^3)$，难以通过。（开 Ofast 可以冲过去）可以将几次相同类型的操作合并为一次操作，这样是跑不满的，实际速度在 $O(w \cdot n^2)$ 级别，$w$ 是小常数。

---

