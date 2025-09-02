# [NOI Online 2022 入门组] 王国比赛

## 题目背景

**经过管理员的考虑，我们打算将民间数据单独存放在最后一个 Subtask 中。这些测试点分数均为 0 分，但是没有通过其中的任何测试点将会视为此题不通过。**

民间数据提供者：@一扶苏一。

## 题目描述

智慧之王 Kri 统治着一座王国。  

这天 Kri 决定举行一场比赛，来检验自己大臣的智慧。  

比赛由 $n$ 道判断题组成，有 $m$ 位大臣参加。现在你已经知道了所有大臣的答题情况，但尚未拿到答案，于是你决定先行预测。  

具体来说，对于第 $i$ 道题，有 $x$ 个大臣选对，$y$ 个大臣选错（显然有 $x+y=m$），如果 $x>y$，那么你预测这题答案为对，否则为错。为了方便，我们保证 $m$ 是奇数。

在统计完成后，你拿到了答案，你想知道通过你的预测方式你最后有几道题预测正确。

## 说明/提示

**【样例 1 解释】**

- 第一题 $x=1,y=2$ 你预测答案为错（即 $0$），实际答案为1，预测错误。
- 第二题 $x=2,y=1$ 你预测答案为对（即 $1$），实际答案为1，预测正确。
- 第三题 $x=2,y=1$ 你预测答案为对（即 $1$），实际答案为1，预测正确。

所以预测正确的题数为 $2$。

**【数据范围】**

对于 $20\%$ 的数据，$n\le 5$，$m=1$。

对于 $50\%$ 的数据，$n\le 10$，$m\le 10$。

对于 $100\%$ 的数据，$1 \le n\le 1000$，$1 \le m\le 1000$，$m$ 为奇数。

## 样例 #1

### 输入

```
3 3
1 0 1
0 1 1
0 1 0
1 1 1```

### 输出

```
2```

## 样例 #2

### 输入

```
6 5
1 0 1 1 1 0
0 1 0 1 1 1
0 0 1 0 1 0
1 0 1 0 1 0
0 1 0 1 0 0
1 0 1 0 1 0```

### 输出

```
4```

## 样例 #3

### 输入

```
见附件中的 kingdom3.in```

### 输出

```
见附件中的 kingdom3.out```

# 题解

## 作者：ShanCreeperPro (赞：19)

## P8254 [NOI Online 2022 入门组] 王国比赛

update：

2022.4.5 更新了~~大家好奇~~的 TLE 做法和突然~~心血来潮~~的 Go 语言做法。

***

这道题有一个坑：

- 题目中为 $n$ 题 $m$ 人，可是输入数据是 $m$ 行 $n$ 列。

还不理解？看看这个样例就知道了：

```cpp
3 3
1 0 1
0 1 1
0 1 0
1 1 1
```

以正常的想法，应该是 `1 0 1`，`0 1 1`，`0 1 0` 这三个数据为一题大臣的判断，可是由于是 $n$ 行 $m$ 列，导致了你需要“竖”着看，即 `1 0 0`，`0 1 1`，`1 1 0` 为三道题的判断。

新手容易上当（包括我都蒙了一会）。

***
**TLE 做法：**

```cpp
inline void part2(){
	fore(i,1,m){
		fore(j,1,n){
			if(a[i][j]==0) b[j].x++;
			else if(a[i][j]==1) b[j].y++;
		}	
	}
	fore(i,1,m){
		if(b[i].x>z) pd[i]=0;
		else pd[i]=1;	
	}
	fore(i,1,n){
		if(pd[i]==ans[i]) sum++;
    }
	write(sum);	
}
```


这个 TLE 的原因非常明显。

所以我们要尽可能把他们放在一起处理。

***

接着讲正解。

- 我们可以定义一个二维数组 $a$ 来存每道题大臣的答案，用 $b$ 存正确的答案，并读入，读入时记得外层循环终止条件为 $m$，内层为 $n$：

（C++）：

```cpp
#define fore(i,x,n) for(int i=x;i<=n;i++)
int n,m,a[MAXX][MAXX],b[MAXX];
fore(i,1,m)
	fore(j,1,n)
    	a[i][j]=read();
fore(i,1,n) b[i]=read();
```

（Go）：
```go
var i,j int
fmt.Scan(&n,&m)
for i=1;i<=m;i++{
	for j=1;j<=n;j++{
		fmt.Scan(&a[i][j])
	}
}
for i=1;i<=n;i++{
	fmt.Scan(b[i])
}
```

- 定义 $x$ 为单个问题猜测正确的人数，$y$ 为猜测错误的人数，如果 $x>y$ 则猜测为对，否则为错：

（C++）：

```cpp
fore(j,1,n){
	x=0; y=0;
	fore(i,1,m){
		if(a[i][j]==1) x++;
		else y++;
	}
	if(x>y) sum=1;
	else sum=0;
```
（Go）：
```go
for j=1;j<=n;j++{
	x=0
	y=0
	for i=1;i<=m;i++{
		if a[i][j]==1{
			x++
		} else {
			y++
		}
		if x>y{
			sum=1
		} else {
			sum=0
		}
```

（这里记得将外层循环设为 $n$，内层为 $m$。）

- 最后进行判断，如果判断对了 `ans` 增加 1，最后输出：

（C++）：

```cpp
	if(sum==b[j]) ans++;
}
write(ans);
```

（Go）：

```go
		if sum==b[j]{
			ans++
		}
	}
}
fmt.Println(ans);
```

时间复杂度 $O(mn)$，可以通过本题。

AC 代码：

（C++）：

```cpp
#include<bits/stdc++.h>
#define int long long
#define fore(i,x,n) for(int i=x;i<=n;i++)
using namespace std;
const int MAXX=1005;
int n,m,a[MAXX][MAXX],b[MAXX];
int x,y,c=1,sum,ans;
const int mod=1;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
inline void write(int x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
signed main(){
	n=read();
	m=read();
	fore(i,1,m)
		fore(j,1,n)
			a[i][j]=read();
	fore(i,1,n) b[i]=read();
	fore(j,1,n){
		x=0; y=0;
		fore(i,1,m){
			if(a[i][j]==1) x++;
			else y++;
		}
		if(x>y) sum=1;
		else sum=0;
		if(sum==b[j]) ans++;
	}
	write(ans);
}
```

（Go）：
```go
package main
import "fmt"
var n,m,x,y,sum,ans int
var a[1005][1005] int
var b[1005] int
var c=1
func main(){
	var i,j int
	fmt.Scan(&n,&m)
	for i=1;i<=m;i++{
		for j=1;j<=n;j++{
			fmt.Scan(&a[i][j])
		}
	}
	for i=1;i<=n;i++{
		fmt.Scan(b[i])
	}
	for j=1;j<=n;j++{
		x=0
		y=0
		for i=1;i<=m;i++{
			if a[i][j]==1{
				x++
			} else {
				y++
			}
			if x>y{
				sum=1
			} else {
				sum=0
			}
			if sum==b[j]{
				ans++
			}
		}
	}
	fmt.Println(ans);
}
```


**后记：**

比赛时脑抽写了个 TLE 的代码气死我了呜呜呜。

---

## 作者：lym12321 (赞：4)

## 题意&分析

有 $m$ 个人回答 $n$ 个判断题，给出每个人的回答和标准答案，需要你判断有多少道题 **正确率大于 50%**。

显而易见，若一道题答对的人数大于答错的人数，我们要将其计入答案。

由于是判断题，答案只有 $0$ 和 $1$ 两种，我们可以按标准答案分为两种情况：

- 答案为 $1$ 时，若回答 $1$ 的人数大于 $\frac{m}{2}$，`ans++`。

- 答案为 $0$ 时，若回答 $1$ 的人数小于 $\frac{m}{2}$，`ans++`。

对于每道题，我们用一个 `cnt` 数组记录答案为 $1$ 的人数即可。

## Code
```cpp
#include<cstdio>

inline int read(){
    int x = 0; char ch = getchar();
    while(ch < '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9'){
        x = (x << 1) + (x << 3) + ch - '0';
        ch = getchar();
    }
    return x;
}

const int maxn = 1e3 + 5;
int n, m, cnt[maxn], ans;

int main(){
    // freopen("kingdom.in", "r", stdin);
    // freopen("kingdom.out", "w", stdout);
    n = read(), m = read();
    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            cnt[j] += read();
        }
    }
    for(int i = 1; i <= n; i++){
        ans += read()?(cnt[i]<<1>m):(cnt[i]<<1<m);
    }
    printf("%d\n", ans);
    return 0;
}
```

其中 `ans += read()?(cnt[i]<<1>m):(cnt[i]<<1<m);` 等效于以下代码：
```cpp
int a = read();
if(a == 1 && cnt[i] * 2 > m) ans++;
if(a == 0 && cnt[i] * 2 < m) ans++;
```

---

## 作者：kaceqwq (赞：1)

# 题目大意:
比赛由 $n$ 道判断题组成，有 $m$ 位大臣参加。

对于第 $i$ 道题，有 $x$ 个大臣选对，$y$ 个大臣选错，如果 $x>y$ ，那么你预测这题答案为对，否则为错。
在统计完成后，你拿到了答案，通过这样预测方式最后有几道题预测正确。

# 思路:
其实思路并不难想。首先根据题意和数据范围我们就可以知道，这是一道简单的模拟题，然后根据题意模拟即可：先输入（要注意 $n$ 和 $m$ 的顺序），然后对于每一道题，查看每一位大臣的答案，如果答对的人数大于答错的人数，我们就预测这一题为正确的，否则预测为错误的。全部的题都预测完后，将预测的答案和标准的答案比较，如果相同计数器就加一，最后输出即可。

# Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
bool a[1005][1005],b[1005];
int dd,dc,sum;
bool flag;
int main()
{
	ios::sync_with_stdio(0);
	//freopen("kingdom.in","r",stdin);
	//freopen("kingdom.out","w",stdout);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++)    //输入，注意m是行,n是列
	for(int j=1;j<=n;j++)
	cin>>a[i][j];	
	for(int i=1;i<=n;i++)    //正确答案
	cin>>b[i];
	for(int i=1;i<=n;i++)
	{
	for(int j=1;j<=m;j++)
	{
	if(a[j][i]==1)
	dd++;   //选择对的大臣数量
	else
	dc++;   //选择错的大臣数量
	}
	if(dd>dc)   //预测为对
	flag=1;
	else        //预测为错
	flag=0;
	if(flag==b[i])    //与正确答案比较，相等就让计数器sum++
	sum++;
	dd=0;
	dc=0;
	}
	cout<<sum<<'\n';    //输出
	return 0; 
}
```


---

## 作者：苏联小渣 (赞：1)

很签到的一道题。输入完后遍历每一列，表示每一道题的选择情况；统计出选对的人数 $p$ 和选错的人数 $q$，若 $p>q$ 则预测此题为对，否则预测为错。最后输入正确答案，判断其与预测答案是否一致即可。

```c++
#include <bits/stdc++.h>
using namespace std;
int n, m, s, yu[1007], x, p, q, a[1007][1007];
int main(){
	//freopen ("kingdom.in", "r", stdin);
	//freopen ("kingdom.out", "w", stdout);
	scanf ("%d%d", &n, &m);
	for (int i=1; i<=m; i++){
		for (int j=1; j<=n; j++){
			scanf ("%d", &a[i][j]);
		}
	}
	for (int j=1; j<=n; j++){
		p = q = 0;
		for (int i=1; i<=m; i++){
			if (a[i][j] == 0) p ++;
			if (a[i][j] == 1) q ++;
		}
		if (p > q) yu[j] = 0;
		else yu[j] = 1;
	}
	for (int i=1; i<=n; i++){
		scanf ("%d", &x);
		if (x == yu[i]) s ++;
	}
	printf ("%d\n", s);
	return 0;
}
```

---

