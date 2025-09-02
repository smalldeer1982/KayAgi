# 题目信息

# The Morning Star

## 题目描述

### 题意简述
本题有多组数据。

给定 $n$ 个点，第 $i$ 个点的坐标为 $x_i$，$y_i$。

现需要将星星和指南针放在任意两个点上，使得星星在指南针的正北、正东、正西、正南、正东南、正东北、正西南或正西北方向，求一共几种放法。（如果对此不太理解结合样例解释）

## 说明/提示

$2\leq n \leq 2 \cdot 10^5$

$-10^9\leq x_i,y_i \leq 10^9$
在第一组数据中：

指南针在 $(0,0)$，星星在 $(-1,-1)$，在指南针的正西南方向。

指南针在 $(0,0)$，星星在 $(1,1)$，在指南针的正东北方向。

指南针在 $(-1,-1)$，星星在 $(0,0)$，在指南针的正东北方向。

指南针在$(-1,-1)$，星星在$(1,1)$，在指南针的正东北方向。

指南针在$(1,1)$，星星在$(0,0)$，在指南针的正西南方向。

指南针在$(1,1)$，星星在$(-1,-1)$，在指南针的正西南方向。

所以答案为6。

在第二组数据中：
 
指南针在$(6,9)$，星星在$(10,13)$，在指南针的正东北方向。

指南针在$(10,13)$，星星在$(6,9)$，在指南针的正西南方向。

所以答案是 2。

## 样例 #1

### 输入

```
5
3
0 0
-1 -1
1 1
4
4 5
5 7
6 9
10 13
3
-1000000000 1000000000
0 0
1000000000 -1000000000
5
0 0
2 2
-1 5
-1 10
2 11
3
0 0
-1 2
1 -2```

### 输出

```
6
2
6
8
0```

# AI分析结果

### 题目翻译
# 晨星

## 题目描述

### 题意简述
本题有多组数据。

给定 $n$ 个点，第 $i$ 个点的坐标为 $x_i$，$y_i$。

现需要将星星和指南针放在任意两个点上，使得星星在指南针的正北、正东、正西、正南、正东南、正东北、正西南或正西北方向，求一共几种放法。（如果对此不太理解结合样例解释）

## 说明/提示

$2\leq n \leq 2 \cdot 10^5$

$-10^9\leq x_i,y_i \leq 10^9$
在第一组数据中：

指南针在 $(0,0)$，星星在 $(-1,-1)$，在指南针的正西南方向。

指南针在 $(0,0)$，星星在 $(1,1)$，在指南针的正东北方向。

指南针在 $(-1,-1)$，星星在 $(0,0)$，在指南针的正东北方向。

指南针在$(-1,-1)$，星星在$(1,1)$，在指南针的正东北方向。

指南针在$(1,1)$，星星在$(0,0)$，在指南针的正西南方向。

指南针在$(1,1)$，星星在$(-1,-1)$，在指南针的正西南方向。

所以答案为6。

在第二组数据中：
 
指南针在$(6,9)$，星星在$(10,13)$，在指南针的正东北方向。

指南针在$(10,13)$，星星在$(6,9)$，在指南针的正西南方向。

所以答案是 2。

## 样例 #1

### 输入

```
5
3
0 0
-1 -1
1 1
4
4 5
5 7
6 9
10 13
3
-1000000000 1000000000
0 0
1000000000 -1000000000
5
0 0
2 2
-1 5
-1 10
2 11
3
0 0
-1 2
1 -2```

### 输出

```
6
2
6
8
0```

### 算法分类
数学、组合数学

### 题解分析与结论
本题的核心在于如何高效地统计满足特定方向关系的点对数量。大多数题解都采用了类似的方法，即通过四个映射表（`map`）来记录点的横坐标、纵坐标、横纵坐标之和、横纵坐标之差，然后根据这些映射表计算满足条件的点对数量。

### 所选高分题解
#### 题解1：作者：lwx20211103 (5星)
**关键亮点**：
- 思路清晰，代码简洁明了。
- 使用四个`map`分别记录横坐标、纵坐标、横纵坐标之和、横纵坐标之差，然后计算排列数。
- 时间复杂度为$O(n)$，效率高。

**核心代码**：
```cpp
ll pailie(int n, int m)
{
	ll ans = 1;
	for (int i = n - m + 1; i <= n; i++)
		ans *= i;
	return ans;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while (t--)
	{
		int n;
		ll ans = 0;//注意long long
		cin >> n;
		map<int, int> mp, mp2, mp3, mp4;
		for (int i = 1; i <= n; i++)
		{
			int x, y;
			cin >> x >> y;
			mp3[x]++;
			mp4[y]++;
			mp[x + y]++;
			mp2[x - y]++;//如题解所示
		}
		for (auto &&i : mp) if (i.second >= 2) ans += pailie(i.second, 2);
		for (auto &&i : mp2) if (i.second >= 2) ans += pailie(i.second, 2);
		for (auto &&i : mp3) if (i.second >= 2) ans += pailie(i.second, 2);
		for (auto &&i : mp4) if (i.second >= 2) ans += pailie(i.second, 2);
		cout << ans << "\n";//完结撒花
	}	
	return 0;
}
```

#### 题解2：作者：_fairytale_ (5星)
**关键亮点**：
- 通过分析指南针与星星的位置关系，将问题转化为统计四个方向的点对数量。
- 使用四个`map`分别记录横坐标、纵坐标、横纵坐标之和、横纵坐标之差，然后计算满足条件的点对数量。
- 代码简洁，逻辑清晰。

**核心代码**：
```cpp
#include<bits/stdc++.h>
#define re register
#define ll long long
#define maxn 200010
using namespace std;
int T;
int n,m;
int x[maxn],y[maxn];
ll ans;
map<int,int>mp1,mp2,mp3,mp4;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
    cin>>T;
    while(T--){
    	mp1.clear(),mp2.clear(),mp3.clear(),mp4.clear();
    	cin>>n;
    	ans=0;
		for(re int i=1;i<=n;++i){
			cin>>x[i]>>y[i];
			mp1[x[i]]++;
			mp2[x[i]-y[i]]++;
			mp3[y[i]]++;
			mp4[x[i]+y[i]]++;
		}
		for(re int i=1;i<=n;++i){
			ans+=mp1[x[i]]+mp2[x[i]-y[i]]+mp3[y[i]]+mp4[x[i]+y[i]]-4;//去掉自己的贡献 
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

#### 题解3：作者：_sunkuangzheng_ (4星)
**关键亮点**：
- 通过排序和遍历的方式统计满足条件的点对数量。
- 使用四个不同的排序规则分别处理横坐标、纵坐标、横纵坐标之和、横纵坐标之差。
- 代码逻辑清晰，但相比前两个题解稍显冗长。

**核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int t,n;
struct p{int x,y;}a[500005];
bool cmp1(p a,p b){return (a.x - a.y) < (b.x - b.y);}
bool cmp4(p a,p b){return (a.x + a.y) < (b.x + b.y);}
bool cmp2(p a,p b){return a.x < b.x;}
bool cmp3(p a,p b){return a.y < b.y;}
signed main(){
    cin >> t;
    while(t --){
        cin >> n;int ans = 0,cnt = 1;
        for(int i = 1;i <= n;i ++) cin >> a[i].x >> a[i].y;
        sort(a+1,a+n+1,cmp1);
        for(int i = 2;i <= n;i ++){
            if((a[i].x - a[i].y) == (a[i-1].x - a[i-1].y)) cnt ++;
            else ans += cnt * (cnt-1),cnt = 1;
        }
        ans += cnt * (cnt - 1),cnt = 1;
        sort(a+1,a+n+1,cmp2);
        for(int i = 2;i <= n;i ++){
            if(a[i].x == a[i-1].x) cnt ++;
            else ans += cnt * (cnt-1),cnt = 1;
        }
        ans += cnt * (cnt - 1),cnt = 1;
        sort(a+1,a+n+1,cmp3);
        for(int i = 2;i <= n;i ++){
            if(a[i].y == a[i-1].y) cnt ++;
            else ans += cnt * (cnt-1),cnt = 1;
        }
        ans += cnt * (cnt - 1),cnt = 1;
        sort(a+1,a+n+1,cmp4);
        for(int i = 2;i <= n;i ++){
            if((a[i].x + a[i].y) == (a[i-1].x + a[i-1].y)) cnt ++;
            else ans += cnt * (cnt-1),cnt = 1;
        }
        ans += cnt * (cnt - 1),cnt = 1;
        cout << ans << "\n";
    }
}
```

### 最优关键思路或技巧
- 使用`map`或排序来统计满足特定方向关系的点对数量。
- 通过横坐标、纵坐标、横纵坐标之和、横纵坐标之差四个维度来分类统计点对。
- 时间复杂度优化到$O(n)$，适合大规模数据处理。

### 可拓展之处
- 类似的问题可以扩展到三维空间，增加一个维度来统计点对。
- 可以结合其他几何问题，如判断点是否在特定区域内。

### 推荐题目
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)
3. [P3374 树状数组 1](https://www.luogu.com.cn/problem/P3374)

---
处理用时：60.01秒