# [CCC 2023 J4/S1] Trianglane

## 题目描述

Bocchi the Builder 刚刚完成了她的最新项目：一条由两排白色等边三角形瓷砖组成的小巷。然而，在最后一刻，灾难降临了！她不小心把黑色油漆洒在了一些瓷砖上。现在，一些瓷砖是湿的，其他瓷砖是干的。Bocchi 必须在所有湿的区域周围放置警示胶带。你能帮她确定她需要多少米的胶带吗？

第一个三角形瓷砖将指向上方。每对相邻的瓷砖（即共享一条边的瓷砖）将指向相反的方向。每块瓷砖的边长为 1 米。

## 说明/提示

**本题采用捆绑测试**。

- 子任务 $1$（$3$ 分）：$C \leq 2 \times 10^3$，黑色三角形不相邻，第二行全部为白色三角形。
- 子任务 $2$（$3$ 分）：$C \leq 2 \times 10^3$，黑色三角形可能相邻，第二行全部为白色三角形。
- 子任务 $3$（$5$ 分）：$C \leq 2 \times 10^3$，黑色三角形可能相邻，第二行可能有黑色三角形。
- 子任务 $4$（$4$ 分）：$C \leq 2 \times 10^5$，黑色三角形可能相邻，第二行可能有黑色三角形。

样例 $1$ 图解：

![](https://cdn.luogu.com.cn/upload/image_hosting/5tfc7u5b.png)

样例 $2$ 图解：

![](https://cdn.luogu.com.cn/upload/image_hosting/4e22mx61.png)

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
5
1 0 1 0 1
0 0 0 0 0```

### 输出

```
9```

## 样例 #2

### 输入

```
7
0 0 1 1 0 1 0
0 0 1 0 1 0 0```

### 输出

```
11```

# 题解

## 作者：_GeorgeAAAADHD_ (赞：3)

这题很显然，两个相邻的黑色三角形，每个黑色的周长都要减去 $1$，因此我们可以一个一个遍历。

那么如何判断相邻？很显然，同行邻列上的黑色三角形相邻，并且奇数列上的黑色三角形也相邻。所以我们可以按照这个思路写代码。

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int c,ans=0;
bool k[2][200001]={0};
int main(){
    cin>>c;
    for(int i=0;i<=1;i++){
    	for(int j=1;j<=c;j++){
    		cin>>k[i][j];
		 }
	}
	for(int i=0;i<=1;i++){
		for(int j=1;j<=c;j++){
			if(k[i][j]){
				ans+=3;
				if(j%2&&i-1==0&&k[i-1][j])ans--;//判断相邻行
				if(j%2&&i+1==1&&k[i+1][j])ans--;
				if(j-1>=1&&k[i][j-1])ans--;    //判断相邻列
				if(j+1<=c&&k[i][j+1])ans--;
			}
		}
	}
	cout<<ans;
    return 0;
}
```

---

## 作者：Leaves_xw (赞：2)

**思路：**

这题主要考察的是，如何判断两个三角形相邻。

那么输入只有 $2$ 行（重要部分只有后两行），每一行或每一列若有黑色相邻的则计数器累加。

假设共有 $n$ 个三角形相邻在一起，则需要的长度为 $n \times 3-(n-1)\times 2$ 个，也就是 $n+2$ 个，那么根据此公式就可以写出代码了。

---

## 作者：ccg12345 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P9302)

记 $ans$ 为最终答案，看到这个题目我是先想到给 $ans$ 赋初始值，即为 $3$ 倍黑三角形的个数。

最后再看有哪些黑三角形有公共边，就可以让 $ans$ 减去公共边数。输出 $ans$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[5][200005];
int main()
{
	int n, ans = 0;
	scanf("%d", &n);
	for(register int i = 1; i <= 2; i++)
		for(register int j = 1; j <= n; j++)
		{
			scanf("%d", &a[i][j]);
			if(a[i][j])
				ans += 3;
		}
	for(register int i = 1; i <= 2; i++)
		for(register int j = 1; j <= n; j++)
		{
			if(a[i][j] && a[i][j - 1])//a[i][j]的左边是黑三角形     
				ans--;
			if(a[i][j] && a[i][j + 1])//a[i][j]的右边是黑三角形
				ans--;
			if(a[i][j] && a[i - 1][j] && j % 2)//奇数列，a[i][j]的上面是黑三角形
				ans--; 
			if(a[i][j] && a[i + 1][j] && j % 2)//奇数列，a[i][j]的下面是黑三角形
				ans--;
		}
	printf("%d", ans);
	return 0; 
}
```


---

## 作者：binomial (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P9302)

# 题目大意
给出一个 2 行 c 列的图形，1 表示黑色三角形，需要用警戒线围起来，问最少需要多少米警戒线。
# 思路
找出相邻三角形，减去共边。
若一个三角形在奇数列，则可以与左边，右边，上（或下）共边，反之，则只能与左或右共边。
（注：本蒟蒻代码只会搜索右边和下边，这样不会重复，所以每次减 2。）
# 代码
```c
#include<bits/stdc++.h>
using namespace std;
int c,h1[200004],h2[200004],ans=0;
int main(){
	cin>>c;
	for(int i=1;i<=c;i++){
		scanf("%d",&h1[i]);
	}
	for(int i=1;i<=c;i++){
		scanf("%d",&h2[i]);
	}//输入
	for(int i=1;i<=c;i++){
		if(h1[i]==1){
			if(h1[i+1]==1){
				ans-=2;
			}//寻找第一行是否有相邻
			if(h2[i]==1&&i%2==1){
				ans-=2;
			}//寻找第一行与第二行是否有相邻
			ans+=3;//每个三角形固定有三米，在上面已经减了相邻
		}
		if(h2[i]==1){
			if(h2[i+1]==1){
				ans-=2;//寻找第二行是否有相邻
			}
			ans+=3;
		}
	}
	printf("%d",ans);//输出答案
	return 0; 
}
```

---

## 作者：Lovely_Elaina (赞：1)

通过分析样例可知，若设有 $x$ 个三角形，$y$ 条边相邻：

- 样例一：全部不相邻，需要 $3\times x$ 米；
- 样例二：有相邻，需要 $3\times x - y$ 米。

那么我们最开始输入的时候，有三角形就给变量 $ans$ 加上 $3$，然后遍历一遍，有相邻的边就给 $ans$ 减上 $1$。

```cpp
#include <iostream>
// #include <bits/stdc++.h>
// #define abs(a) (a<0?-a:a)
// #define max(a,b) (a>b?a:b)
// #define min(a,b) (a<b?a:b)
// #define int __int128
// #define int long long
// #define int unsigned int
#define endl '\n'
using namespace std;

int c,ans;
int a[105][200005];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(NULL);

    cin >> c;
    for(int i = 1; i <= 2; i++){
        for(int j = 1; j <= c; j++){
            cin >> a[i][j];
            if(a[i][j]) ans += 3;
        }
    }

    for(int i = 1; i <= 2; i++){
        for(int j = 1; j <= c; j++){
            if(a[i][j] && a[i][j-1]) ans--;
            if(a[i][j+1] && a[i][j]) ans--;
            if(a[i+1][j] && a[i][j]&&j%2) ans--;
            if(a[i-1][j] && a[i][j]&&j%2) ans--;
        }
    }
    
    cout << ans << endl;
    return 0;
}
```

---

## 作者：Red0rangE (赞：1)

## 题意理解

给出一个正整数 $n$，再给出一个 $2$ 行 $n$ 列的数字阵，```1``` 表示有三角形，需要围起来，如果三角形相邻可以省去围栏，求围栏总长。

## 思路阐述

遍历每一个位置，如果有三角形就将答案加上周长，再判断左右上下相邻，如果相邻就将答案减一（因为同一条重合的边会被找到两次，所以不需要一下子减去二）。

**注意上下相邻的情况：只有三角形处于列号为奇数时才共边**。

## 代码呈现

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
bool mp[3][200005];//数组
int x;//当前数字
int cnt;//答案计算

signed main(){
    
    scanf("%d",&n);
    for (int i=1;i<=n;i++){
        scanf("%d",&x);
        if (x) mp[1][i]=1;//x是1，标记为1
    }
    for (int i=1;i<=n;i++){
        scanf("%d",&x);
        if (x) mp[2][i]=1;
    }//分行输入
    for (int i=1;i<=n;i++){
        if (mp[1][i]){//这里有三角形
            cnt+=3;//答案加上周长
            if (mp[1][i-1]) cnt--;//左边相邻
            if (mp[1][i+1]) cnt--;//右边相邻
            if (mp[2][i] && i&1) cnt--;//下边相邻，是奇数列
        }
    }
    for (int i=1;i<=n;i++){//第二行同理
        if (mp[2][i]){
            cnt+=3;
            if (mp[2][i-1]) cnt--;
            if (mp[2][i+1]) cnt--;
            if (mp[1][i] && i&1) cnt--;//上边相邻，是奇数列
        }
    }
    printf("%d",cnt);//输出
    return 0;
    
}

```

希望可以帮到各位大佬。

---

## 作者：Vct14 (赞：0)

### 题意

给定一个由 $0$ 和 $1$ 组成的 $2\times c$ 的矩阵，每个数表示一个边长为 $1$ 的三角形。矩阵中中 $1$ 表示这个三角形为黑色。求黑色部分的周长。

### 思路

设有 $a$ 个黑色三角形，若所有黑色三角形互不相邻，则周长为 $3a$。随后遍历每一个位置，若此三角形有相邻的三角形，则将周长减 $1$。

注意，虽然一条重合的边会造成周长多 $2$，但是因为同一条重合的边会被遍历到 $2$ 次（两个三角形各 $1$ 次），所以每次只需减去当前三角形的 $1$ 条边。

我们可以发现，当黑色三角形在同一列时，若为此列为第奇数列，则相邻；

![](https://cdn.luogu.com.cn/upload/image_hosting/d0bl5zbj.png)

若为第偶数列，则不相邻。

![](https://cdn.luogu.com.cn/upload/image_hosting/0r65l2aw.png)

### 代码

```c++
#include<bits/stdc++.h>
using namespace std;

int a[4][200002];//在左右留出空位，则判断时不用判断边界 
int ans;//周长 

void find(int i,int j){//判断相邻 
	if(a[i][j-1]==1) ans--;//左 
	if(a[i][j+1]==1) ans--;//右 
	if(j%2==1){//记得判断奇偶列 
		if(a[i-1][j]==1) ans--;//上 
		if(a[i+1][j]==1) ans--;//下 
	}
}

int main(){
	int c;
	cin>>c;
	for(int i=1; i<=2; i++){
		for(int j=1; j<=c; j++){
			cin>>a[i][j];
			if(a[i][j]==1) ans++;//三角形个数 
		}
	}
	ans*=3;//3 条边 
	for(int i=1; i<=2; i++) for(int j=1; j<=c; j++) if(a[i][j]==1) find(i,j);//判断相邻 
	cout<<ans;
	return 0; 
}
```

---

## 作者：_AyachiNene (赞：0)

# 题意：
给一个 $2$ 行 $n$ 列由三角形组成的矩阵，$1$ 表示这个三角形需要围起来，求围起来的长度（相邻的 $2$ 个三角形不用重合部分不用围）。
# 思路：
遍历整个矩形，设三角形个数为 $x$，答案的初值就为 $3x$，如果有一个三角形与一个三角形相邻，那么答案就减一。

**注意：上下相邻的三角形需要看列数的奇偶性，为偶数不会影响答案。**
# Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int c,a[114][114514*2],ans;
int main()
{
	cin>>c;
	for(int i=1;i<=2;i++)
		for(int j=1;j<=c;j++)
		{
			cin>>a[i][j];
			if(a[i][j])
				ans+=3;     //初值为三角形个数*3 
		}
	for(int i=1;i<=2;i++)
		for(int j=1;j<=c;j++)
		{
			if(a[i][j]&&a[i][j-1])      
				ans--;										
			if(a[i][j+1]&&a[i][j])
				ans--;                       //左右相邻的情况 
				
			if(a[i+1][j]&&a[i][j]&&j%2)			//上下相邻的情况 
				ans--;
			if(a[i-1][j]&&a[i][j]&&j%2)
				ans--;
		}
	cout<<ans;
	return 0; 
}
```


---

## 作者：watcher_YBH (赞：0)

# 思路：
我们可以遍历两列三角形，如果此时的位置是黑三角形，就判断左右是否也是黑三角形，如果左右也是，那么就可以分别抵消一条边；如果此时的列数为奇数，那么它也可以与上下发生抵消。
# 代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX = 2e5+5;
int n,ans;
int a[5][MAX];
int main(){
	cin>>n;
	for(int i = 1; i<=2; i++)
		for(int j = 1; j<=n; j++)
			cin>>a[i][j];
	for(int i = 1; i<=2; i++){//遍历所三角形 
		for(int j = 1; j<=n; j++){
			if(a[i][j] == 1){//此处是黑三角形 
				ans += 3;
				if(a[i][j-1]==1)ans--;
				//左边是黑三角形，边数抵消一个 
				if(a[i][j+1]==1)ans--;
				//右边是黑三角形，边数抵消一个
				if(i==1&&a[i+1][j]==1&&j%2==1)ans--;
				//列数为奇数，行数为1，下面有黑三角形，边数抵消一个 
				if(i==2&&a[i-1][j]==1&&j%2==1)ans--;
				//列数为奇数，行数为1，下面有黑三角形，边数抵消一个 
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}

```


---

## 作者：Yun_Mengxi (赞：0)

[[题目传送门]](https://www.luogu.com.cn/problem/P9302)

[[推销博客]](https://www.luogu.com.cn/blog/758416/solution-p9302)

### [题意分析]

显然的，单独的一个黑色三角形需要 $3$ 米栅栏，而对于有相邻的黑色三角形的黑色三角形来说，肯定只需要把不相邻的边围上栅栏就行了，所以需要的栅栏为三条边去掉相邻的边之后剩下的边数米。

而怎么判断相邻呢？分为两种情况：

- 第一种，当前的三角形尖端朝外（也就是下标为奇数），那么就需要判断上（下）、左、右三个方向相不相邻。

- 第二种，当前的三角形尖端朝内（也就是下标为偶数），那么就需要判断左右，因为尖端是不需要围栅栏的。

- 如果当前下标为 $1$（或 $C$），不需要进行特殊处理，因为左边（或右边）默认是白色三角形，不影响答案。

直接把上下两个数组扫一遍，判断相邻就可以了，时间复杂度 $\text{O(C)}$。

### [代码]

如下（复制可以获得尊贵的棕名和高贵的 Tag，马蜂奇特，见谅）：

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a),i##END=(b);i<=i##END;i++)
#define Rof(i,b,a) for(int i=(b),i##END=(a);i>=i##END;i--)
#define go(u) for(int i=head[u];i;i=nxt[i])
#define int long long
#define endl '\n'
using namespace std;

//Int:
int c;
int a[200005];
int b[200005];
int ans=0;

//Func:
inline int read(){ //丑恶快读（
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return x*f;
}
signed main(){
	//Code:
	c=read();
	For(i,1,c) a[i]=read();
	For(i,1,c) b[i]=read();
	For(i,1,c) //扫一遍 a 数组
	{
		if(i%2==1&&a[i]) //第一种情况
		{
			ans+=3; //假设为单独的三角形
			if(a[i-1]) //如果左边相邻
			{
				ans--;
			}
			if(a[i+1]) //如果右边相邻
			{
				ans--;
			}
			if(b[i]) //如果下面相邻
			{
				ans--;
			}
		}
		if(i%2==0&&a[i]) //第二种情况
		{
			ans+=3;
			if(a[i-1]) //左边不相邻
			{
				ans--;
			}
			if(a[i+1]) //右边不相邻
			{
				ans--;
			}
		}
	}
	For(i,1,c) //扫一遍 b 数组
	{
		if(i%2==1&&b[i]) //第一种情况
		{
			ans+=3;
			if(b[i-1]) //如果左边相邻
			{
				ans--;
			}
			if(b[i+1]) //如果右边相邻
			{
				ans--;
			}
			if(a[i]) //如果下面相邻
			{
				ans--;
			}
		}
		if(i%2==0&&b[i]) //第二种情况
		{
			ans+=3;
			if(b[i-1]) //左边相邻
			{
				ans--;
			}
			if(b[i+1]) //右边相邻
			{
				ans--;
			}
		}
	}
	cout<<ans<<endl; //输出答案
	return 0;
}
```

[[AC 记录]](https://www.luogu.com.cn/record/109247215)

---

## 作者：CleverRaccoon (赞：0)

## 题目

[题目传送门](https://www.luogu.com.cn/problem/P9302)

有黑色和白色的三角形，现在需要用围栏将黑色三角形围起来，如果黑色三角形相邻，可以省一些围栏，求栅栏的长度是多少。

## 思路

对于第 $k$ 行的第 $i$ 个三角形：

- 如果 $i$ 是奇数，这个三角形有可能和**左面、右面和下面**的三角形重边（黑色是当前三角形，灰色是会和它重边的三角形）。

![](https://cdn.luogu.com.cn/upload/image_hosting/tnebwc88.png)

- 如果 $i$ 是偶数，这个三角形有可能和**左面、右面**的三角形重边（黑色是当前三角形，灰色是会和它重边的三角形）。

![](https://cdn.luogu.com.cn/upload/image_hosting/chtbc9bi.png)

所以，我们只要遍历每行的每一个三角形：

1. 如果它**左面没有三角形**，那么将答案加一。

2. 如果它**右面没有三角形**，那么将答案加一。

3. 如果它的**列数是奇数**，并且它**上面（或下面）没有三角形**，那么将答案加一。

## 代码

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int C = 2e5 + 5;
int a[C], b[C], c, ans;

int main() {
    cin >> c;
    for(int i = 1; i <= c; ++i)
        cin >> a[i];
    for(int i = 1; i <= c; ++i)
        cin >> b[i];
    // 第一行
    for(int i = 1; i <= c; ++i)
        if(a[i]) {
            if(!a[i - 1])    // 左
                ++ans;
            if(!a[i + 1])   // 右
                ++ans;
            if(!(i % 2 == 1 && b[i]))   // 下（但是要注意，只有列数为奇数时才会有下边相邻的情况）
                ++ans;
        }
    // 第二行
    for(int i = 1; i <= c; ++i)
        if(b[i]) {
            if(!b[i - 1])   // 左
                ++ans;
            if(!b[i + 1])   // 右
                ++ans;
            if(!(i % 2 == 1 && a[i]))   // 上（但是要注意，只有列数为奇数时才会有下边相邻的情况）
                ++ans;
        }
    cout << ans;
    return 0;
}
```

谢谢大家！完结撒花！


---

