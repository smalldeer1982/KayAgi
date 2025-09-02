# Sagheer, the Hausmeister

## 题目描述

# Sagheer, the Hausmeister

## 题目大意

有一栋楼房，里面有很多盏灯没关，为了节约用电Sagheer决定把这些灯都关了。

这楼有 n 层，最左边和最右边有楼梯。每一层有 m 个房间排成一排。这栋楼可以被表示成一个 n 行 m + 2 列的矩阵，其中每行第一个和最后一个格点表示楼梯， 剩余 m 个格点表示房间。

现在Sagheer在最底层的最左边楼梯，他想要关掉所有的灯。他每次可以走到相邻的房间，如果在楼梯口可以上下楼梯。他打算关掉所有开着的灯，在他没有将一层的所有灯都关闭前他不会上楼。现在求他最少需要走多少步可以关闭所有灯。

注意Sagheer不需要返回原处，最终可以停留在任意一个地方。

## 样例 #1

### 输入

```
2 2
0010
0100
```

### 输出

```
5
```

## 样例 #2

### 输入

```
3 4
001000
000010
000010
```

### 输出

```
12
```

## 样例 #3

### 输入

```
4 3
01110
01110
01110
01110
```

### 输出

```
18
```

# 题解

## 作者：mouseboy (赞：4)

康了康唯一的题解，说没必要用DP，我就给出DP的解法。

~~这其实是道水题~~ ，唯一的坑是有可能楼上没有开的灯，坑了我们机房的一堆人（ WA on test 4 ），剩下的就是DP。

我们用 $a[n][0]$,表示第 $n$ 层的第一个房间，用 $a[n][1]$，表示第 $n$ 层的最后一个房间。

这里提供一个收集型的写法。

所以可得状态转移方程为 $dp[i][j] = \min(dp[i + 1][!j] + m + 2, dp[i + 1][j] + a[i + 1][!j] \times 2 + 1)$ 对于 $j$,表示第 $i$ 层的楼梯口，可以从下层（$i+1$ 层）的另一边的楼梯口走来，也可以直接从同边走上来，最后取最小值。

最后附上代码。
```cpp
#include <iostream>
using namespace std;
const int Maxn = 20;
int a[Maxn][2], dp[Maxn][2], n, m, s;
char c;
int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= m + 1; j++) {
      cin >> c;
      if (c == '1') {
        a[i][0] = max(a[i][0], m + 1 - j), a[i][1] = max(a[i][1], j);//求出最左边和最右边
      }
    }
  }
  dp[n][1] = m + 1;//初始化（应为我们可以确定从初始点走到最右边是 $m+1$ 步）
  for (int i = n - 1; i >= 1; i--) {
    for (int j = 0; j <= 1; j++) {
      dp[i][j] = min(dp[i + 1][!j] + m + 2, dp[i + 1][j] + a[i + 1][!j] * 2 + 1);//求值
    }
  }
  for (s = 1; s < n && !a[s][0]; s++) {
  }//过滤没灯的那几层
  cout << min(dp[s][0] + a[s][1], dp[s][1] + a[s][0]);
  return 0;
}
```

---

## 作者：Blikewsr (赞：3)

### 题目传送门
[CF812B - Luogu](https://www.luogu.com.cn/problem/CF812B)

[CF812B - Codeforces](https://codeforces.com/problemset/problem/812/B)

### 题目简述
给定一个楼层图，用 `01` 表示，`1` 表示开灯的房间，最左边和最右边为楼梯间，用 `0` 表示，我们在 **最底层最左边** 的楼梯口，求至少要走多少步才能关掉所有的灯。

### 思路分析
注意到，最高几层可能全部是 `0`，说明这几层没有灯，我们跟本不用走，所以我们可以先枚举每一层，找到 **最高的且有灯开着的** 一层开始走。

我们定义一个二维数组 `cnt[N][2]`，其中 $cnt_{i, 0}$ 表示从第 $i$ 层楼 **左边** 进入的情况下，关掉第 $i$ 层及其楼上所有层的灯的 **最小步数**，$cnt_{i, 1}$ 表示从第 $i$ 层楼 **右边** 进入的情况下，关掉第 $i$ 层及其楼上所有层的灯的 **最小步数**。

然后在定义一个两个一维数组 `lef[N]` 和 `rig[N]`，其中 $lef_i$ 表示第 $i$ 层楼 **最左边亮着灯** 的房间号，$rig_i$ 表示第 $i$ 层楼 **最右边亮着灯** 的房间号

现在，我们来考虑以下转移方程。

显然的，每一层的步数只受它上一层的步数和本层亮灯的房间影响的。

其次，最优的走法肯定是要么走完一整层从另一边上到上一层，要么走到这一层里所在楼梯口最远的亮着灯的房间在原路返回在上到上一层，所以我们有 $4$ 种走发：

1. 从第 $i$ 层 **左边** 进入，**右边** 上楼。
2. 从第 $i$ 层 **左边** 进入，**左边** 上楼。
3. 从第 $i$ 层 **右边** 进入，**左边** 上楼。
4. 从第 $i$ 层 **右边** 进入，**右边** 上楼。

对于第 $1$ 种走法，我们可以得到：
$$cnt_{i, 0} = cnt_{i + 1, 1} + (m + 1) + 1$$

对于第 $2$ 种走法，我们可以得到：
$$cnt_{i, 0} = cnt_{i + 1, 0} + rig_i \times 2 + 1$$

对于第 $3$ 种走法，我们可以得到：
$$cnt_{i, 1} = cnt_{i + 1, 0} + (m + 1) + 1$$

对于第 $4$ 种走法，我们可以得到：
$$cnt_{i, 1} = cnt_{i + 1, 1} + (m - (lef_i - 1)) \times 2 = cnt_{i + 1, 1} + (m - lef_i + 1) \times 2 + 1$$

知道了所有的走法的转移方程，既然我们要求最小步数，那么我们直接让对应的转移方程分别取最小值就可以了。

即：

$$cnt_{i, 0} = \min(cnt_{i + 1, 0} + rig_i \times 2, cnt_{i + 1, 0} + rig_i \times 2) + 1$$

$$cnt_{i, 1} = \min(cnt_{i + 1, 0} + (m + 1), cnt_{i + 1, 1} + (m - lef_i + 1) \times 2) + 1$$

**注意：** 转移方程上面的加一是因为上楼区要在楼梯间走一步，所以 **最高的且有灯开着的** 那一层楼不用上楼。

**其他细节见代码注释**

### 代码实现

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, m, h, mp[20][107], lef[20], rig[20];
int cnt[20][2];
char s[20][107]; 
signed main() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++ i)
        cin >> s[i]; // 因为输入没有空格，先用字符类型输入
    for (int i = 1; i <= n; ++ i) {
        lef[i] = m + 1, rig[i] = 0;
        for (int j = 1; j <= m; ++ j) {
            mp[i][j] = (int)(s[i][j] - '0');
            if (mp[i][j]) {
                if (lef[i] == m + 1) lef[i] = rig[i] = j; // 最左边亮着灯的房间
                else rig[i] = j; // 最右边亮着灯的房间
                if (!h) h = i; // 最高的且有灯开着的一层
            }
        }
    }
    if (!h) { // 整个楼房没有房间开灯，直接走人
        cout << "0\n";
        return 0;
    }
    cnt[h][0] = rig[h], cnt[h][1] = m - lef[h] + 1;
    for (int i = h + 1; i <= n; ++ i) {
        // 转移方程
        cnt[i][0] = min(cnt[i - 1][0] + rig[i] * 2, cnt[i - 1][1] + m + 1);  
        cnt[i][1] = min(cnt[i - 1][1] + (m - lef[i] + 1) * 2, cnt[i - 1][0] + m + 1);
        // 往上走一层
        ++ cnt[i][0];
        ++ cnt[i][1];
    }
    cout << cnt[n][0] << '\n'; // 因为在左侧，所以输出 cnt[n][0]
    return 0;
}
```

### [**提交记录**](https://codeforces.com/contest/812/submission/292175378)

---

## 作者：StarryWander (赞：2)

## 本题使用深度优先搜索即可。

### 题外话：

AC 后看到很多人使用了 DP ，但对于这一题来说**完全没有必要**，不仅增加了时间复杂度还更难去想。

### 思路：

对于 DFS 大家第一时间肯定会想到按照每一个房间，枚举向左房间或者向右房间遍历，遇到梯子就上去，但是这样的复杂度完全过不了。所以我们考虑**枚举每一层**。对于每一层，我们有两种选择，一是选择关闭本层的所有的灯然后**回到原来的楼梯**，二是关闭本层的所有灯再**到对面的楼梯**。然后再花 $1$ 的单位上楼。但是对于这两种不同的情况，还需要再分类讨论起始位置：**人在左边楼梯还是在右边楼梯**。

### 细节

此题着重考察细节，因此，会有很多实现细节需要注意。

- 对于每次关掉一层的灯，其实求的就是关掉最左边（右边）花费的路程（至于左边还是右边取决于你所在的楼梯位置）。所以需要在输入的时候**统计每一层的最左边和最右边的灯的位置**。

- 枚举每种情况：

	- 如果处于左边楼梯并回来，**花费就等于** $2\times$ **最右边的楼梯位置** $+1$ 。
   - 如果处于左边楼梯直接到右边楼梯，**花费就等于** $m+1$ 。
   
   - 如果处于右边楼梯并回来，**花费就等于** $2\times m-$  **最左边的楼梯位置** $+1$ 。
   - 如果处于右边楼梯直接到左边楼梯，**花费就等于** $m+1$ 。
   
   - 别忘了 $+1 $ ，也就是**上楼花费的时间**。
   
- 最后考虑边界，在输入的时候**统计最上层的灯在第几层**，如果没有统计到灯，直接输出 $0$ 即可。对于统计出来的最高层灯，我们**只需要关到最高层**，无需再上楼了，这时候就可以直接统计最小值。

- 还有一种特殊的情况是某层（**但不是最高层**）没有灯需要关，**直接花费** $ 1 $ **单位上楼即可**。
   

## code：


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
struct node{
	int l,r;
};
bool a[205][205];
node lt[25];//统计每层最左（右）的楼梯。
int n,m,h=-1,ans=1e9+10;
void dfs(int flr,int stp,bool k){
	if(flr==h){//到达需要关灯的最高层。
		if(k==0) stp+=lt[flr].r;
		ans=min(ans,stp);
		return;
	}
	else if(lt[flr].l==-1&&lt[flr].r==-1){//本层没有灯需要关。
		dfs(flr-1,stp+1,k);
		return;
	} 
	else if(k==0){//人在左边楼梯。
		dfs(flr-1,stp+(2*lt[flr].r)+1,0);
		dfs(flr-1,stp+m+1,1);
	} 
	else if(k==1){//人在右边楼梯。
		dfs(flr-1,stp+(2*(m-lt[flr].l))+1,1);
		dfs(flr-1,stp+m+1,0);
	} 
}
int main(){
	n=read(),m=read();
	m++;
	for(int i=1;i<=20;i++) lt[i].l=lt[i].r=-1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=m;j++){
			char c;
			cin>>c;
			a[i][j]=c-'0';
		}
		for(int j=0;j<=m;j++){//统计每层最左（右）的楼梯。
			int k=m-j;
			if(a[i][j]&&lt[i].l==-1) lt[i].l=j;
			if(a[i][k]&&lt[i].r==-1) lt[i].r=k;
			if(lt[i].l!=-1&&lt[i].r!=-1) break;
		}
		if(h==-1&&(lt[i].l!=-1||lt[i].r!=-1)) h=i;//统计最高层需要关的灯。
	}
	if(h==-1){
		cout<<0;
		return 0;
	} 
	dfs(n,0,0);//初始位置为 n ，步数为 0 ，在左边。
	cout<<ans;
    return 0;
}
```


---

## 作者：All_Wrong_Answer (赞：0)

[luogu 题目传送门](https://www.luogu.com.cn/problem/CF812B)

[CF 题目传送门](https://codeforces.com/problemset/problem/812/B)

## 思路：

**DFS**，但是枚举每个房间显然会 T，所以枚举楼层，考虑如何关闭本楼层的所有灯后再上楼，用 $mq$ 表示当前到哪一层了。

**分 $4$ 种情况：**

1. 从左侧楼梯出发，向右走，一直走到右边楼梯，一路关灯，最后从右边楼梯上楼，代价为 $y+2$。
2. 从左侧楼梯出发，向右走，关完本楼所有灯后往回走，回到左侧楼梯上楼，代价为 $(rightmax_{mq}-1) \times 2 + 1$。
3. 从右侧楼梯出发，向左走，一直走到左边楼梯，一路关灯，最后从左边楼梯上楼，代价为 $y+2$。
4. 从右侧楼梯出发，向左走，关完本楼所有灯后往回走，回到右侧楼梯上楼，代价为 $(y+2-leftmax_{mq}) \times 2 + 1$。

### 输入时要处理的：
1. 本楼层有没有灯要关。
2. 本楼层最左边的灯在哪。
3. 本楼层最右边的灯在哪。
4. 最高的有灯楼层是哪一层。

$leftmax_i$ 表示第 $i$ 层楼最左边的灯的位置；
$rightmax_i$ 表示第 $i$ 层楼最右边的灯的位置，$dmax$ 表示最高的有灯的楼层。

DFS 时，如果本楼层无灯要关且楼上还有灯没关，直接上楼。

DFS 的边界条件就是最高的有灯楼层，即 $mq=dmax$。

**记得上楼也有 $1$ 的代价！**

## 完整代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
long long x,y;
long long left_max[105];//含义同上 
long long right_max[105];//含义同上 
bool flag[105];//这层楼有没有灯 
long long da=999999999;
const long long sl=1;
long long d_max=0;//含义同上 
void dfs(long long mq,long long s,long long wz){
	if(mq==d_max){
		if(wz==1) da=min(da,s+right_max[mq]-1);
		else da=min(da,s+y+2-left_max[mq]);
		return ;
		//边界 
	}
	if(flag[mq]==false){
		dfs(mq+1,s+sl,wz);
		return ;
	} 
	if(wz==1){
		dfs(mq+1,s+(right_max[mq]-1)*2+sl,1);//上文操作2 
		dfs(mq+1,s+y+1+sl,2);//上文操作1
	}
	else{
		dfs(mq+1,s+((y+2-left_max[mq])*2)+sl,2);//上文操作4
		dfs(mq+1,s+y+1+sl,1);//上文操作3
	}
}
int main(){
	cin>>x>>y;
	for(long long i=x;i>=1;i--){
		for(long long j=1;j<=y+2;j++){
			char u;
			cin>>u;
			if(flag[i]==false&&u=='1'){
				flag[i]=true;
				left_max[i]=j;
			}
			if(u=='1'){
				 right_max[i]=j;
				 d_max=max(d_max,i);
			}
		}
	}
    if(d_max==0){
    	cout<<0;
    	return 0;
    	//一开始所有灯都是关的可以直接输出0 
	}
	dfs(1,0,1);
	cout<<da<<endl;
	return 0;
}#include <bits/stdc++.h>
using namespace std;
long long x,y;
long long left_max[105];//含义同上 
long long right_max[105];//含义同上 
bool flag[105];//这层楼有没有灯 
long long da=999999999;
const long long sl=1;
long long d_max=0;//含义同上 
void dfs(long long mq,long long s,long long wz){
	if(mq==d_max){
		if(wz==1) da=min(da,s+right_max[mq]-1);
		else da=min(da,s+y+2-left_max[mq]);
		return ;
		//边界 
	}
	if(flag[mq]==false){
		dfs(mq+1,s+sl,wz);
		return ;
	} 
	if(wz==1){
		dfs(mq+1,s+(right_max[mq]-1)*2+sl,1);//上文操作2 
		dfs(mq+1,s+y+1+sl,2);//上文操作1
	}
	else{
		dfs(mq+1,s+((y+2-left_max[mq])*2)+sl,2);//上文操作4
		dfs(mq+1,s+y+1+sl,1);//上文操作3
	}
}
int main(){
	cin>>x>>y;
	for(long long i=x;i>=1;i--){
		for(long long j=1;j<=y+2;j++){
			char u;
			cin>>u;
			if(flag[i]==false&&u=='1'){
				flag[i]=true;
				left_max[i]=j;
			}
			if(u=='1'){
				 right_max[i]=j;
				 d_max=max(d_max,i);
			}
		}
	}
    if(d_max==0){
    	cout<<0;
    	return 0;
    	//一开始所有灯都是关的可以直接输出0 
	}
	dfs(1,0,1);
	cout<<da<<endl;
	return 0;
}
```

[CF 通过记录](https://codeforces.com/contest/812/submission/302166017)

---

## 作者：chenlongli (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF812B)
### 思路
我们可以使用深度优先搜索来通过这道题目。

对于每层楼，我们有两种可能上楼，一种是从左边上楼，一种是从右边上楼，我们可以暴力枚举选择哪种方式上楼，但要特判的是，如果说你现在这层楼的上面每一层楼的灯都是闭合状态，那么你就没有必要再上楼了。

如果你现在位于左侧，那么你要先走到这层楼最右边的的灯，如果你现在位于右侧，那么你要先走到这层楼最左边的灯。

我们可以提前处理每一行最右边的灯和最左边的灯，然后就可以直接快速计算每一行所需的时间了，当然，除了计算左右移动的时间，还要计算上下移动的时间。
### code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m;
long long l[20],r[20],ans=10000000,sum=0;
long long da[20],zda[20];
char a;
long long c=0;
void dfs(long long p,long long w)
{
	if (p==c)
	{
        if (w==1)
        {
            sum=sum+(r[p]-1);
        }
        else
        {
            sum=sum+(m-l[p]);
        }
		ans=min(ans,sum);
        for (long long i=1;i<=n;i++)
        {
            zda[i]=da[i];
        }
        if (w==1)
        {
            sum=sum-(r[p]-1);
        }
        else
        {
            sum=sum-(m-l[p]);
        }
		return;
	}
	if (l[p]!=0)
	{
    	if (w==1)
    	{
    		sum=sum+(r[p]-1)*2;
            da[p]=1;
    		dfs(p+1,1);
    		sum=sum-(r[p]-1)+(m-r[p]);
            da[p]=m;
    		dfs(p+1,m);
    		sum=sum-(r[p]-1)-(m-r[p]);
    	}
    	else
    	{
    		sum=sum+(m-l[p])*2;
            da[p]=m;
    		dfs(p+1,m);
    		sum=sum-(m-l[p])+(l[p]-1);
            da[p]=1;
    		dfs(p+1,1);
    		sum=sum-(l[p]-1)-(m-l[p]);
    	}
	}
	else
	{
	    if (w==1)
	    {
	        dfs(p+1,1);
	        sum=sum+(m-1);
	        dfs(p+1,m);
	        sum=sum-(m-1);
	    }
	    else
	    {
	        dfs(p+1,m);
	        sum=sum+(m-1);
	        dfs(p+1,1);
	        sum=sum-(m-1);
	    }
	}
	return;
}
int main()
{
	cin>>n>>m;
    m=m+2;
    c=0;
	for (long long i=n;i>=1;i--)
	{
		for (long long j=1;j<=m;j++)
		{
			cin>>a;
			if (a=='1')
			{
				if (l[i]==0)
				{
					l[i]=j;
				}
				else
				{
					r[i]=j;
				}
			}
		}
        if (r[i]==0)
        {
            r[i]=l[i];
        }
        if (l[i]!=0)
        {
            c=max(c,i);
        }
	}
    if (c==0)
    {
        cout<<0<<endl;
        return 0;
    }
	dfs(1,1);
	cout<<ans+c-1<<endl;
}
```

---

