# Xenia and Weights

## 题目描述

希妮亚有一套砝码和天平，每个砝码的重量为1到10之间的整数。希妮亚要玩一个关于天平和砝码的游戏，为此，她一个一个地给秤盘加砝码。第一个砝码放在左边，第二个在右边，第三个在左边，第四个在右边，以此类推。希妮亚想把m个砝码全部加到天平上。 简单地在天平上加砝码没啥意思，所以希妮亚制定了一些规则。首先，她不能连续把两个相同重量的砝码放在天平上。也就是说，对于第i个砝码(1<=i<m)，第i个的重量应该与第i+1个的重量不同。第二，每当希妮亚在某个秤盘上加砝码，她想让这个秤盘的载重超过另一个的载重。也就是说，对应的秤盘上的重量之和必须严格大于另一个秤盘上的重量之和。 我们给希妮亚所有类型的砝码。她有无数个特定重量的砝码。你的任务是帮助希妮亚在天平上放m个砝码，或者告诉希妮亚这是不可能做到的。

## 样例 #1

### 输入

```
0000000101
3
```

### 输出

```
YES
8 10 8
```

## 样例 #2

### 输入

```
1000000000
2
```

### 输出

```
NO
```

# 题解

## 作者：jdsb (赞：6)

## 题意
告诉你若干个砝码的质量，每个砝码可以放任意次，你有左右两个盘，你需要交替着把砝码放在两个盘中，总共放$m$次，保证每次放置在一个盘后，这个盘的重量要大于另一个盘，并且这次放置的砝码质量和上一次的不能相同，判断能否执行完这一过程，如果能就输出任一解决方案
## 分析
按照题意模拟，进行$dfs$，先用$vis$数组存哪些砝码可以使用，然后进行模拟，如果是第奇数次放置，就加入左盘，否则放右盘，记录下每次放置的砝码，如果放置完了就输出，如果最后也不能放置完就输出$NO$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5;
int vis[15],n,a[N];
void print()
{
	puts("YES");
	for(int i=1;i<=n;i++) printf("%d ",a[i]);
}
void dfs(int k,int ls,int rs,int last)
{
	if(k==n+1)
	{
		print();
		exit(0);
	}
	for(int i=1;i<=10;i++)
	{
		if(!vis[i]) continue;
		if(i==last) continue;
		if(k%2==1)
		{
			if(ls+i>rs) 
			{
				a[k]=i;
				dfs(k+1,ls+i,rs,i);
			}
		}
		else
		{
			if(rs+i>ls)
			{
				a[k]=i;
				dfs(k+1,ls,rs+i,i);
			}
		}
	}
}
int main()
{
	for(int i=1;i<=10;i++)
	{
		char c=getchar();
		if(c-'0'==1) vis[i]=1;
	}
	scanf("%d",&n);
	dfs(1,0,0,0);
	puts("NO");
	return 0;
}
```


---

## 作者：AKPC (赞：5)

### 思路
这题的思路并不难。考虑 dfs，但是直接爆搜，复杂度高达 $10^m$。所以在这里还需要考虑一些贪心剪枝。

首先定义一个 $a$ 数组保存所有可以使用的砝码重量。从第一次放砝码开始，假设要放置砝码的托盘重量 $l$，另一边的 $r$，从小到大枚举放置的砝码重量（令其为 $t$），判断 $l+t>r$ 是否成立即可，当然还要判断上次有没有用这个砝码。更小的砝码可以让下一次放置的选择更多，所以可以用贪心。

代码实现的话每次 dfs 交换两边托盘的重量，这样可以让代码更简介。设一个 tmp，如果出现了正确答案，就把 tmp 从 $0$ 改为 $1$，就没必要再搜了，这就是剪枝。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int a[11],n,tip,ans[1001];
char ch;
bool tmp;
void dfs(int k,int l,int r,int la){
	if (k==n){
		tmp=1;
		puts("YES");
		return;
	}
	for (int i=1;i<=tip;i++)
		if (a[i]+l>r&&a[i]!=la&&!tmp){
			ans[k+1]=a[i];
			dfs(k+1,r,l+a[i],a[i]);
		}
}
signed main(){
	for (int i=1;i<=10;i++){
		cin>>ch;
		if (ch=='1') a[++tip]=i;
	}
	cin>>n;
	dfs(0,0,0,0);
	if (ans[n]==0) puts("NO");
	else for (int i=1;i<=n;i++) cout<<ans[i]<<' ';
	return 0;
}
```


---

## 作者：RiceFruit (赞：4)

## 题目大意

[题目传送门](https://www.luogu.com.cn/problem/CF339C)

给你一个长度为 $10$ 的 01 字符串，若第 $i$ 位为 $1$，则表示你拥有正无穷个质量为 $i$ 的砝码，你要用这些砝码在左盘和右盘依次放置（先放左盘）$m$ 次，保证在每一次放置完成之后，放置的那一个盘要比另一个盘重，并且相邻两次不能放同一个砝码，若能够做到，请在第一行输出 `YES` 并在第二行输出方案，否则输出 `NO`.

## 思路

我们使用 `dfs`，每一次都从到到小枚举砝码，如果能用，则选择并`dfs`。

实现详见代码。

## CODE
```cpp

#include <bits/stdc++.h>
using namespace std;
const int N=11,M=10011;
int n,m;
int a[N];//表示能用的砝码
int ans[M];//储存答案
void dfs(int dq,int last,int now)
{//dq为要加砝码的盘的质量，last为另一个盘的质量，now为当前再放第几次
	if(now>m){//满足条件则输出
		cout<<"YES"<<endl;
		for(int i=1;i<=m;i++)
		cout<<ans[i]<<' ';
		cout<<endl;
		exit(0);//结束整个程序
	}
	for(int i=n;i>=1;i--){//从大到小枚举
		if(a[i]+dq>last&&a[i]!=ans[now-1]){//选择能用的砝码
			ans[now]=a[i];
			dfs(last,dq+a[i],now+1);//左右互换
		}
	}
}
int main()
{
	string s;cin>>s;
	for(int i=0;i<10;i++){
		if(s[i]=='1')a[++n]=i+1;
	}
	cin>>m;
	dfs(0,0,1);
	cout<<"NO"<<endl;
	return 0;
}
```

---

## 作者：Phoenix114514 (赞：3)

# CF339C Xenia and Weights
## 思路
两个限制条件。
- 这次放的不等于上一次放的。
- 对应的秤盘上的重量之和必须严格大于另一个秤盘上的重量之和。

首选 dfs，但是暴力搜索的时间复杂度是 $O(10^m)$，$m$ 最大是 $1000$，直接超时。所以我们还要考虑优化一下。

用一个数组存 $1 \sim 10$ 的的砝码。在处理如何在搜索中使满足条件 2，可以这样：令 $l$ 为要放的砝码总质量，$r$ 为另一边砝码的总质量，$d$ 为此时放的砝码质量，只需判断 $l+d>r$，因为天平两边可以交换，所以下次搜索时，将这次的 $r$ 放在参数 $l$ 里，$l+d$ 放在参数 $r$ 里。

剪枝方面：用一个布尔型的全局变量，如果已经有一种合法的情况了，就不要再搜了。

详见代码。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
string s;//存十个砝码的状态
int m,a[12];//a数组存1～10的砝码是否存在
int ans[1005];//记录答案
bool flag;//剪枝
void dfs(int now,int l,int r,int last){//now表示现在放了多少个，l表示左边的，r表示右边的，last表示上一个放的是哪个砝码
    if (now==m){//边界条件
        flag=true;
        return;
    }
    for (int i=1;i<=10;i++){//直接枚举
        if (a[i]+l>r&&a[i]!=last&&!flag){//条件
            ans[now+1]=a[i];
            dfs(now+1,r,l+a[i],a[i]);//深度优先搜索
        }
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>s>>m;
    for (int i=0;i<s.size();i++){
         if (s[i]=='1')a[i+1]=i+1;
    }//初始化a
    dfs(0,0,0,0);
    if (!flag)cout<<"NO";//不成功
    else{
        cout<<"YES\n";
        for (int i=1;i<=m;i++)cout<<ans[i]<<" ";
    }//成功
    return 0;
}
```

---

## 作者：叶ID (赞：2)

题目链接：[CF339C](https://www.luogu.org/problem/CF339C)

【广告】在个人博客阅读：[这里](https://toxic2018.ml/1838/)

****

这题已经有较为完善的题目翻译。[在我之前的一篇题解](https://ji-suan-ke.blog.luogu.org/solution-cf339c)思路是暴力搜索（复杂度是正确的），而这篇题解用的是动态规划的思路。

### 题目大意

你被允许使用$1..10$中的若干个数。

一开始有两个数$a,b$，初始值均为$0$。

你需要对这两个数交替操作（先操作哪个无关紧要），**一共** $m$次。每次操作你需要将所操作的数加上 **一个** 你 **被允许使用** 的数。每次操作需要满足：

- 加上的数和你 **上一次** 操作不同（对于第一次操作，没有限制）
- 操作后被操作的数必须 **严格大于** 另一个数

问你是否可能合法地进行$m$次操作。如果可能，需要构造出一种方法。

$1 \leq m \leq 1000$

****

由于动态规划的路径记录实际上非常简单，我们暂且不考虑构造出一种方案，只考虑是否有可能。

### 状态设计

最容易想到的状态设计是：

$dp[1..m][1..10\cdot m][1..10\cdot m]$，其中$dp[i][j][k][t]$表示已经操作$i$次，并且此时$a$的值为$j$，$b$的值为$k$，并且上一次操作加上的数是$t$时，是否有可能。

然而根据题目的数据范围，要开的数组是：$dp[1..1000][1..10000][1..10000][1..10]$，显然不可以。

我们注意到上面的状态设计中存在极多的冗余信息。我们发现，影响下一步决策的只有：

- **上一次** 操作时加上的数（因为这次就不能再用了）
- **上一次** 操作后，被操作数减去另一个数所得的值（本次操作加的数必须大于这个）

那么只需将这两个作为状态即可。

- 第一维：$0..n$，$i$表示在第$i$次 **操作后**。**取值范围分析：** 理论上需要$1..n$，而具体实现时，我们需要增加一个$0$，表示未进行任何操作。这样可以降低编程难度（或避免复制粘贴代码）
- 第二维：$0..10$，本次操作加上的数（即，**下次操作** 不能再用的数）。**取值范围分析：** 加上的数取值范围是$1..10$，而在没有进行任何操作时，我们认为上次加上的数是$0$，表示没有任何一个数不能在下一次使用。
- 第三维：$0..10$，本次操作后，被操作数减去另一个数的值（假如操作的是$a$，那么这个值就是$a-b$，否则是$b-a$）。**下一次操作** 加上的数必须大于这个。**取值范围分析：** 每次操作后，这一维的取值范围为$1..9$。特别地，如果第一次操作加上的是$10$，那么这一维能取到$10$。在没有进行任何操作时，我们令这一维为$0$，表示对下一次操作加上的数的最小值没有限制。

状态描述：$dp[i][cant][gt]$

我们在$dp$数组中用`0`描述“不能做到”，`1`描述“可以做到”。

利用这种状态设计，我们甚至不用关心本次操作的是哪个数了。

### 初始化

没有进行任何操作的情况是 **可能做到的**（显然）。

没有任何操作时，令$cant = 0$表示下一次（第一次）没有不能取的值，令$gt = 0$表示对下一次加的数的最小大小没有限制。

对于$i=0$的其他状态，不能做到。

对于$i>1$的其他状态，都是未知情况。由于$dp$是基于“或”操作的（即，能够转移到当前状态的状态只要有一个可能做到，当前状态就可以做到），因此初始化为$0$。

初始化：

$dp[0][0][0] = 0$

其他情况都是赋值为$0$，如果开的是全局数组则会自动初始化为0，无需手动初始化。

### 状态转移

我们用$has[num]$表示你是否允许使用数字$num$。

考虑状态$dp[i-1][cant][gt]$，那么该状态可以转移到$dp[i][num][num-gt]$，其中$num$满足$has[val]\ \&\&\ num\neq cant\ \&\&\ num > gt$。

这非常好理解。至于为什么转移到的是$num-gt$：

假设第$i-1$操作的数是$a$，那么$gt = a-b$。

第$i$次操作的数应该是$b$，则有：


$gt_{new}$

$= b_{new} - a_{new}$

$= (b+num)-a$

$= num + (b-a)$

$= num - (a-b)$

$= num - gt$ 

### 记录路径

普通的动态规划是很容易记录路径的。我们在更新一个状态时，可以顺便在这个状态中存储 **转移到这个状态的前一个状态**。

最终$dp$完成时，由于答案并不关心最后一次操作完成后的$cant$和$gt$值，我们需要在$dp[n][0..10][0..10]$任意取出一个可以做到的值（即，$dp[n][0..10][0..10]=1$）。

然后根据存储的“上一个状态”向前回溯，并重新计算出每次加上的数，放入一个数组。

由于我们对于一次操作，有$gt_{new} = num - gt$，可以得出：

如果$dp[i][cant_{new}][gt_{new}]$由$dp[i-1][cant][gt]$转移而来，那么第$i$次操作加上的数$put_i$就是$gt_{new} + gt$

最后输出答案即可。

****

### 程序与细节注释

```cpp
// status: [Accepted]
// oj:     [luogu]

#include<bits/stdc++.h>
using namespace std;

int has[11]; // 是否允许使用某个数
int put[1001]; // 放入的数，用于最后回溯并输出答案的时候
int n; // 需要操作的次数

struct State {
    // 状态
    bool can;
    // 来历
    int p1;
    int p2;
    int p3;
}dp[1001][11][11];
//DP维度：
// 1. 填充长度
// 2. 不能填充的数字 (0:没有限制)
// 3. 至少填充的数字 (0:没有限制)

int main() {
    ios::sync_with_stdio(false);

    for(int i=1;i<=10;i++) {
        char c;
        cin>>c;
        has[i] = c-'0';
    }

    cin>>n;
    
    // 初始化
    dp[0][0][0].can = 1;
    // 枚举操作次数
    for(int i=1;i<=n;i++) {
        // 针对 上一个状态：上一次加上的数
        for(int cant=0;cant<=10;cant++) {
            // 针对 上一个状态：上一次操作后，操作数减去另一个数的值
            for(int gt=0;gt<=10;gt++) {
                // 上一个状态 不能做到，不进行转移。
                if(!dp[i-1][cant][gt].can) continue;
                // 枚举大于gt的数用来加
                for(int num=gt+1;num<=10;num++) {
                    // 和上一次冲突，或本来就不能取
                    if(!has[num] || num==cant) continue;
                    // 此处使用引用来表示下一次可以转移到的状态，能够简化代码
                    State &ret = dp[i][num][num-gt];
                    // 上一个状态有解，当前肯定有解
                    ret.can = 1;
                    // 记录状态的“来历”
                    ret.p1 = i-1;
                    ret.p2 = cant;
                    ret.p3 = gt;
                }
            }
        }
    }

    int c1 = 0, c2 = 0, c3 = 0;

    for(int i=0;i<=10;i++) {
        for(int j=0;j<=10;j++) {
            // 随便找一个有解的状态。
            if(dp[n][i][j].can) {
                c1 = n;
                c2 = i;
                c3 = j;
                break;
            }
        }
    }

    // 有解
    if(c1 || c2 || c3) {
        cout<<"YES"<<endl;
        // 向前回溯，存储答案
        while(c1>0) {
            State &curr = dp[c1][c2][c3];
            int n1 = curr.p1;
            int n2 = curr.p2;
            int n3 = curr.p3;
            // 依据：put[i] = gt_new +gt
            put[c1] = c3 + n3;
            // 向前跳到上一个状态
            c1=n1;c2=n2;c3=n3;
        }
        // 输出答案
        for(int i=1;i<=n;i++) {
            if(i>1) cout<<' ';
            cout<<put[i];
        }
        cout<<endl;
    }
    // 无解
    else {
        cout<<"NO"<<endl;
    }
}

```

评测记录：[R24108985](https://www.luogu.org/record/24108985)


---

## 作者：The_foolishest_OIer (赞：0)

直接爆搜，枚举每一个能用的砝码质量，如果当前放的是第 $2k + 1$ 个砝码，就给左盘质量增加，否则给右盘质量增加。

当然，如果当前取的砝码质量上一次刚刚用过，那么也是不合法的。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 1005;
int m;
int vis[15],a[N];
string s;
void close(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
void dfs (int pos,int lw,int rw,int last){ // 分别记录当前放的是第几个；左盘总质量；右盘总质量；和上一次放的砝码质量
	if (pos > m){ // 找到一个合法方案
		cout << "YES\n"; 
		for (int i = 1 ; i <= m ; i++) cout << a[i] << ' ';
		exit(0); // 直接结束程序
	}
	for (int i = 1 ; i <= 10 ; i++){
		if (vis[i] == 0 || i == last) continue;
		if (pos % 2 == 1){ // 如果当前回合放在左盘
			if (lw + i > rw){ // 判断是否可行
				a[pos] = i;
				dfs(pos + 1,lw + i,rw,i);
			}
		}else{
			if (rw + i > lw){
				a[pos] = i;
				dfs(pos + 1,lw,rw + i,i);
			}
		}
	}
}
signed main(){
	close();
	cin >> s;
	cin >> m;
	for (int i = 0 ; i < 10 ; i++) if (s[i] == '1') vis[i + 1] = 1;
	dfs(1,0,0,0);
	cout << "NO";
	return 0;
}
```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF339C)

## 思路

由于 $1\le m \le 1000$，砝码总数 $n\le 10$，所以我们考虑直接搜索。

按照题意，每次搜索时循环枚举砝码。如果上一次放的左边这次就放右边，反之则放左边。如果上一次放的砝码和当前相同就跳过。如果这次放入后某一边能够保证严格大于另一边才继续搜索，否则跳过。

搜索时用一个数组 ``ans[k]`` 记录，``k`` 表示放的第 $k$ 个砝码重量。

如果总共已经放了 $m$ 个就达到要求了，直接输出后结束程序即可。

- 搜索进行完没结束，输出 ``NO``。

- 一个小小的优化：读入数据后只把存在的砝码（即值为 $1$ 的位）存起来再 dfs，会快很多。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=20;
int n,a[N],m,ans[1<<N];//ans 数组其实只需要开 1000 多一点的大小就够了。
string s;
void dfs(int l,int r,int last,bool op,int cnt){
//左边重量，右边重量，上次放的重量，这次该放 0 左边/1 右边，总共放的数量。
	if(cnt==m){//已经放完了肯定符合要求，输出即可。
		cout<<"YES\n";
		for(int i=1;i<=m;++i)cout<<ans[i]<<" ";
		exit(0);
	}
	for(int i=1;i<=n;++i){
		if(last!=a[i]){
			ans[cnt+1]=a[i];//不要用队列代替！会有没清空全的问题！
			if(!op&&l+a[i]>r)dfs(l+a[i],r,a[i],1,cnt+1);
			else if(op&&l<r+a[i])dfs(l,r+a[i],a[i],0,cnt+1);
		}
	}
	return ;
}
signed main(){
	cin>>s>>m;
	for(int i=0;i<s.size();++i){
		if(s[i]=='1')a[++n]=i+1;//上文中优化。
	}
	dfs(0,0,0,0,0);
	cout<<"NO";
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/158487552)

---

## 作者：qinmingze (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF339C)

### 思路

看完题目，我们便能很直观地看出本题考察的是**搜索**。因此我们只需要对每次的放置过程进行模拟就可以了。如果当前是左盘放的话，我们需要判断加入当前的砝码后，左盘的总质量是否**严格大于**右盘的总质量，如果严格大于，便可以继续搜索，否则，继续找砝码，如果到最后，也没找到，那么当前情况**舍去**。右盘同理。

#### 注意

- 如果第 $i$ 位的数字为 $1$，那么质量为 $i$ 的砝码的数量是无限的。

- 放砝码时，必须是一次左盘，一次右盘。

- 每次放的砝码的质量**不能**与上次放的砝码的质量相同

### 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 2000;

int m, n = 0;

int a[N];

bool vis[N];

int ans[N];

void print(){//输出方案。
	for(int i = 1; i <= m; i++) cout << ans[i] << " ";
	return ;
}

void dfs(int k, int l, int r, int last){
	if(k == m + 1){//有解。
		puts("YES");
		print();
		exit(0);
	}
	for(int i = 1; i <= n; i++){
		if(last == a[i]) continue;//不能与上次相同。
		if(k % 2 == 0){//放左盘。
			if(l + a[i] > r){//左盘的质量严格大于右盘。
				ans[k] = a[i];
				dfs(k + 1, l + a[i], r, a[i]);//继续搜索。
				ans[k] = 0;
			}
		}else{//放右盘。
			if(r + a[i] > l){//右盘的质量严格大于左盘。
				ans[k] = a[i];
				dfs(k + 1, l, r + a[i], a[i]);//继续搜索。
				ans[k] = 0;
			}
		}
	}
}

int main(){
	string s;
	cin >> s >> m;
	for(int i = 0; i < s.size(); i++){
		if(s[i] == '1') a[++n] = i + 1;//加砝码。
	}
	dfs(1, 0, 0, 0);
	puts("NO");//无解。
	return 0;
}
```

---

## 作者：Genshin_ZFYX (赞：0)

一道简单的 dfs。

我们用 $f$ 数组存下 $1$ 到 $10$ 哪些数，然后开始搜索。$x$ 表示现在要放第几个砝码，如果 $x=m$，则输出并结束程序。我们把接下来要放的砝码的重量枚举一遍，如果 $x$ 是奇数，我们把放在左边的天平上，否则放在右边的天平上，再判断重量是否大于另一个天平，如果可以的话把重量记录在数组里面，然后继续搜索。

如果搜索完了之后还是没有找到合适的方案，则输出 `NO`。

AC 代码：
```
#include<bits/stdc++.h>
using namespace std;
int f[15],a[1005],m;
void dfs(int x,int p1,int p2)
{
	if(x>m)
	{
		cout<<"YES"<<'\n';
		for(int i=1;i<=m;i++)
		cout<<a[i]<<" ";
		exit(0);
	}
	for(int i=1;i<=10;i++)
	if(f[i]&&a[x-1]!=i)
	if(x%2==1)
	{
		if(p1+i>p2)
		{
			a[x]=i;
			dfs(x+1,p1+i,p2);
		}
	}
	else
	{
		if(p2+i>p1)
		{
			a[x]=i;
			dfs(x+1,p1,p2+i);
		}
	}
}
int main()
{
	cin.tie(0)->sync_with_stdio(0);
    for(int i=1;i<=10;i++)
    {
    	char c;cin>>c;
    	if(c=='1')f[i]=1;
	}
	cin>>m;
	dfs(1,0,0);
	cout<<"NO";
    return 0; 
}
```

---

## 作者：incra (赞：0)

### 前言
参考了官解。
### 题解
令 $f_{u,diff,last}$ 表示在第 $u$ 次，两个数的差（如果 $u$ 是奇数，就是第一个数减第二个数，否则是第二个数减第一个数）为 $diff$，最后一次选的是 $last$ 时是否有答案。

设能选的所有砝码集合为 $all$，则对于每一个 $\forall x\in all$，只要满足 $x\neq last$ 且 $diff-x<0$（在下一轮计算时 $diff$ 也要是正的），就能用 $f_{u+1,-(diff-x),x}$ 来更新自己。

方案记录一下后驱就好了。
### 代码
```
#include <bits/stdc++.h>
#define x first
#define y second
#define pb push_back
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair <int,int> PII;
const int dx[] = {1,-1,0,0},dy[] = {0,0,1,-1};
bool LAST = false;
istream& operator >> (istream& in,char* s) {
    if (LAST) return in;
	char ch = cin.get ();
	while ((isspace (ch) || ch == '\n') && ch != EOF) ch = cin.get ();
	int n = 0;
	while (!(isspace (ch) || ch == '\n') && ch != EOF) s[n++] = ch,ch = cin.get ();
	s[n] = '\0';
	if (ch == EOF) LAST = true;
	return in;
}
const int N = 1010,M = 20;
string s;
int n;
vector <int> all;
bool f[N][M][M];
int nxt[N][M][M];
bool DFS (int u,int diff,int last) {
	if (f[u][diff][last]) return f[u][diff][last];
	if (u > n) return true;
	for (int x : all) {
		if (x != last && diff - x < 0) {
			if (DFS (u + 1,-(diff - x),x)) {
				f[u][diff][last] = true;
				nxt[u][diff][last] = x;
				return true;
			}
		}
	}
	return false;
}
int main () {
	cin >> s >> n;
	for (int i = 1;i <= 10;i++) {
		if (s[i - 1] == '1') all.push_back (i);
	}
	if (!DFS (1,0,0)) puts ("NO");
	else {
		puts ("YES");
		int u = 1,diff = 0,last = 0;
		for (;u <= n;u++) {
			int num = nxt[u][diff][last];
			cout << num << ' ';
			last = num,diff = -(diff - num);
		}
	}
	return 0;
}
```

---

## 作者：Imken (赞：0)

题意：给你无限多给定重量的砝码，天平上放 $m$ 个，每次放置后的一边载重必须严格大于另一边，且连续两次放置砝码不能相同。确定是否可行，并输出一组可行的方案（字典序最小）。

看到字典序最小就很容易可以想到贪心构造。但是，纯贪心构造很明显会出错。

在构造几组数据拍两下之后，例如这组：

```
0110100100
10
```

纯贪心构造的结果是：

```
2 3 2 3 5 8 后面无解
```

暴搜（$O(10^m)$ 的暴力）的结果是：

```
2 3 2 5 8 5 2 5 8 5
```

这个时候就应该不难想到想到深搜 + 贪心剪枝的做法了。大胆写一下，就可以通过了：

```
int n, last = 0;
// 天平 
i64 tp[2];
char op[15];
vector<int> res;

int dfs(int cur, int dep)
{
	if (dep == n + 1) return 1;
	for (int j = tp[cur ^ 1] - tp[cur] + 1; j <= 10; j++) {
		if (!op[j] || j == last) continue;
		last = j;
		tp[cur] += j;
		if (dfs(cur ^ 1, dep + 1)) {
			res.push_back(j);
			return 1;
		}
		tp[cur] -= j;
	}
	return 0;
}

int main()
{
	init_io();
	for (int i = 1; i <= 10; i++) {
		cin >> op[i];
		op[i] -= '0';
	}
	cin >> n;
	res.reserve(n);
	if (!dfs(0, 1)) {
		cout << "NO" << '\n';
		return 0;
	}
	cout << "YES" << '\n';

	reverse(res.begin(), res.end());
	for (auto x : res) cout << x << ' ';
	return 0;
}
```

---

## 作者：Macesuted (赞：0)

[题面](https://www.luogu.com.cn/problem/CF339C)

## 题意

现在有一个天平，你拥有一些种类的砝码，这些砝码的重量均在 $1 \sim 10$ 间且对于每一种砝码你有无数多个。现在按照两个要求依次放置 $m$ 个砝码，要求如下:

1. 相邻两次放置操作不能放置相同的砝码
2. 每次放下砝码后必须保证放下砝码的这个盘的总重量大于另一盘。

其中第一个砝码必须放在左盘，第二个砝码必须放右盘，第三个放左盘，以此类推。

## 分析

直接dfs所有可能的方案，尝试将所有你拥有的砝码放入当前盘，并且按照两个要求进行剪枝。有一些细节，详见代码。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

bool vis[11];
int record[1005];  //用来记录每轮放置的砝码重量
int m;

//五项参数分别表示当前轮到放到哪盘、左盘重量、右盘重量、已放置砝码数量、上一次放置的砝码重量
bool dfs(int turn, int left, int right, int times, int front) {
    if (times)
        if (turn) {  //如果左右盘的重量并不满足要求2
            if (left <= right)
                return false;
        } else if (left >= right)
            return false;
    if (times == m) {  //如果已放置m个砝码
        puts("YES");
        for (int i = 0; i < times; i++)
            printf("%d ", record[i]);
        puts("");
        return true;
    }
    bool check = false;
    for (int i = 1; i <= 10; i++)
        if (vis[i] && i != front) {  //尝试所有可能放置的砝码，放入当前盘
            record[times] = i;
            if (!turn)
                check |= dfs(!turn, left + i, right, times + 1, i);
            else
                check |= dfs(!turn, left, right + i, times + 1, i);
            if (check)  //一旦任意一种情况满足条件，则直接return
                return true;
        }
    return check;
}

int main() {
    int t;
    scanf("%d", &t);
    for (int i = 10; i; i--) {  //拆分t
        vis[i] = t % 10;
        t /= 10;
    }
    scanf("%d", &m);
    if (!dfs(0, 0, 0, 0, -1))
        puts("NO");
    return 0;
}
```

---

## 作者：aRenBigFather (赞：0)

一个贪心方法，不能过完但是可以得很多分(开始就是这样写的)
```cpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
string aa;
bool flag[20];
ll lweight,rweight;
int m;
vector<int> ans;
int last = -1;
int getmin(int low){
    for(int i=low+1;i<=10;i++)
        if(flag[i] && i != last) {
            last = i;
            return i;
        }
    return -1;
}
int main(){
    cin >> aa >> m;
    memset(flag,0,sizeof flag);
    for(int i=0;i<aa.size();i++)
        if(aa[i] == '1') flag[i+1] = true;
    lweight = 0,rweight = 0;
    bool cant = false;
    for(int i=1;i<=m;i++){
        if(i & 1){
            //put to left
            int dt = rweight - lweight;
            int mincan = getmin(dt);
            if(mincan == -1){
                cant = true;
                break;
            }
            lweight += mincan;
            ans.push_back(mincan);
        }else{
            //put to right
            int dt = lweight - rweight;
            int mincan = getmin(dt);
            if(mincan == -1){
                cant = true;
                break;
            }
            rweight += mincan;
            ans.push_back(mincan);
        }
    }
    if(cant){
        cout << "NO" << endl;
        return 0;
    }else{
        cout << "YES" << endl;
        for(int i=0;i<ans.size();i++){
            if(i == 0) cout << ans[i];
            else cout << " " << ans[i];
        }
    }
    return 0;
} 
```

正解是很简单的dfs
纪录路径的时候有个方法直接开全局变量(以前都不知道可以这样，然后就不用dfs传路径参数下去了)

```cpp
#include <bits/stdc++.h>
using namespace std;
string aa;
bool flag[20];
int ans[1010];
int m;
bool can = false;
bool dfs(int step,char nowdir,int lastWei,int lwei,int rwei){
	//cout << "step:" << step << " lwei:" << lwei << " rwei:" << rwei << endl;
	if(step == m+1){
		return true;
	}
	if(nowdir == 'R'){
		//放右边
		int dt = lwei - rwei;
		bool cant = true;
		for(int i=dt+1;i<=10;i++){
			if(flag[i] && i != lastWei){
				cant = false;
				ans[step] = i;
				if(dfs(step+1,'L',i,lwei,rwei+i)) return true;
			}
		}
		if(cant) return false;
	}else if(nowdir == 'L'){
		//放左边
		int dt = rwei - lwei;
		bool cant = true;
		for(int i=dt+1;i<=10;i++){
			if(flag[i] && i != lastWei){
				cant = false;
				ans[step] = i;
				if(dfs(step+1,'R',i,lwei+i,rwei)) return true;
			}
		}
		if(cant) return false;
	}
}
int main(){
	cin >> aa >> m;
	memset(flag,0,sizeof flag);
    for(int i=0;i<aa.size();i++)
        if(aa[i] == '1') flag[i+1] = true;
    if(dfs(1,'L',-1,0,0)){
    	cout << "YES" << endl;
		for(int i=1;i<=m;i++){
			if(i == 1) cout << ans[i];
			else cout << " " << ans[i];
		}
	}else{
		cout << "NO" << endl;
	}
	return 0;
}
```

---

