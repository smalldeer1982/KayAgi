# [ABC057B] Checkpoints

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc057/tasks/abc057_b

$ xy $ 平面があり、その上に $ N $ 人の学生がいて、$ M $ 個のチェックポイントがあります。  
 $ i $ 番目の学生がいる座標は $ (a_i,b_i)\ (1≦i≦N) $ であり、番号 $ j $ のチェックポイントの座標は $ (c_j,d_j)\ (1≦j≦M) $ です。   
 これから合図があり、各学生はマンハッタン距離で一番近いチェックポイントに集合しなければなりません。   
 2つの地点 $ (x_1,y_1) $ と $ (x_2,y_2) $ 間のマンハッタン距離は $ |x_1-x_2|+|y_1-y_2| $ で表されます。  
 ここで、$ |x| $ は $ x $ の絶対値を表します。  
 ただし、一番近いチェックポイントが複数ある場合には、番号が最も小さいチェックポイントに移動することとします。  
 合図の後に、各学生がどのチェックポイントに移動するかを求めてください。

## 说明/提示

### 制約

- $ 1≦N,M≦50 $
- $ -10^8≦a_i,b_i,c_j,d_j≦10^8 $
- 入力は全て整数である。

### Sample Explanation 1

$ 1 $ 番目の学生と各チェックポイント間のマンハッタン距離は以下の通りです。 - 番号 $ 1 $ のチェックポイントへのマンハッタン距離は $ |2-(-1)|+|0-0|=3 $ - 番号 $ 2 $ のチェックポイントへのマンハッタン距離は $ |2-1|+|0-0|=1 $ したがって、最も近いチェックポイントの番号は $ 2 $ であるため、$ 1 $ 行目には $ 2 $ と出力します。 $ 2 $ 番目の学生と各チェックポイント間のマンハッタン距離は以下の通りです。 - 番号 $ 1 $ のチェックポイントへのマンハッタン距離は $ |0-(-1)|+|0-0|=1 $ - 番号 $ 2 $ のチェックポイントへのマンハッタン距離は $ |0-1|+|0-0|=1 $ 最も近いチェックポイントが複数ある場合は、番号が最も小さいチェックポイントに移動するため、$ 2 $ 行目には $ 1 $ と出力します。

### Sample Explanation 2

同じ座標に複数のチェックポイントが存在する場合もあります。

## 样例 #1

### 输入

```
2 2
2 0
0 0
-1 0
1 0```

### 输出

```
2
1```

## 样例 #2

### 输入

```
3 4
10 10
-10 -10
3 3
1 2
2 3
3 5
3 5```

### 输出

```
3
1
2```

## 样例 #3

### 输入

```
5 5
-100000000 -100000000
-100000000 100000000
100000000 -100000000
100000000 100000000
0 0
0 0
100000000 100000000
100000000 -100000000
-100000000 100000000
-100000000 -100000000```

### 输出

```
5
4
3
2
1```

# 题解

## 作者：封禁用户 (赞：4)

这不是个 $O(nm)$ 暴力么。

### $\sf{Solution}$

- 两点之间曼哈顿距离公式： $|x_1-x_2|-|y_1-y_2|$ （ $x$ 为横坐标， $y$ 为纵坐标）。

套个两重循环求 min 就完事了。

### $\sf{Code}$

```cpp
#include<iostream>
#include<cmath>
using namespace std;
int n,m,a[55],b[55],c[55],d[55];
int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1;i<=n;++i)
		cin>>a[i]>>b[i];//student
	for(int i=1;i<=m;++i)
		cin>>c[i]>>d[i];
	for(int i=1;i<=n;++i)
	{
		int minn=1e9,t=0;//初始化
		for(int j=1;j<=m;++j)
		{
			int p=abs(a[i]-c[j])+abs(b[i]-d[j]);//曼哈顿距离
			if(p<minn)
				minn=p,t=j;//求 min
		}
		cout<<t<<"\n";
	}
	return 0;
}
```

---

## 作者：cjZYZtcl (赞：1)

超级大暴力

~~不知道为啥会评为黄题~~

以上纯属个人吐槽

------------
来讲讲正解。

其实这题就是暴力。

对于每个学生暴力找到离他最近的检查站，然后输出就可以了。

- 注意距离是曼哈顿距离，不是欧几里得距离。
- 注意AT输出要换行

### code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[55], b[55], c[55], d[55];
inline int read(){
	int x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * m;
}
inline void write(int x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
signed main(){
	int n = read(), m = read();
	for(int i = 1; i <= n; i++){
		a[i] = read(), b[i] = read();
	}
	for(int i = 1; i <= m; i++){
		c[i] = read(), d[i] = read();
	}
	int mi;
	for(int i = 1; i <= n; i++){
		mi = 1;
		for(int j = 2; j <= m; j++){
			if(abs(a[i] - c[j]) + abs(b[i] - d[j]) < abs(a[i] - c[mi]) + abs(b[i] - d[mi])) mi = j;
		}
		write(mi);
		putchar('\n');
	}
}
```
完毕。


---

## 作者：zfn07 (赞：1)

此题比较简单，只需循环求最小值即可.
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,m,a[55],b[55],c[55],d[55],i,j,minv=1e9,minn;//a,b数组存储学生坐标;c,d数组存储检查站坐标.minv存最小值,minn存储最近的检查站编号
	cin>>n>>m;
	for(i=1;i<=n;i++)
		cin>>a[i]>>b[i];
	for(i=1;i<=m;i++)
		cin>>c[i]>>d[i];
	for(i=1;i<=n;i++){
		minv=1e9;
		for(j=1;j<=m;j++)
			if(abs(c[j]-a[i])+abs(d[j]-b[i])<minv){//如果第j个检查站离第i个学生的距离比原来的近,就更新最小值和最近的检查站编号
				minv=abs(c[j]-a[i])+abs(d[j]-b[i]);
				minn=j;
			}
		cout<<minn<<endl;
        //循环完一次就输出这次的最小值
	}
	return 0;
} 
```


---

## 作者：Aisaka_Taiga (赞：0)

这道题数据范围很小，可以直接枚举。

根据题目里给的公式计算每一个学生到每一个检查站的曼哈顿距离，然后挨个比较找出最小的就好了。

注意 minn 的初值一定要大，否则你就会和[我](https://www.luogu.com.cn/record/list?pid=AT2522&user=wwwaax&page=1)一样。

核心代码：
```cpp
for(int i=1;i<=n;i++)
	{
		int minn=9999999999,k;//minn赋个大一点的初值存当前的最短曼哈顿距离，k存第几个检查站 
		for(int j=1;j<=m;j++)//开始枚举检查站 
	    {
	    	int o=abs(x[i]-xx[j])+abs(y[i]-yy[j]);//计算当前学生到此检查站的曼哈顿距离 
	    	if(minn>o)//比较 
	    	minn=o,k=j;//替换 
		}
		cout<<k<<endl;//输出 
	}
```


---

## 作者：zct_sky (赞：0)

### Solution:
-----
数据范围： $1\leqq N,M\leqq 50$，便能想到这题暴力 $O(nm)$ 也能过。

那么只需遍历每一个学生，再暴力寻找曼哈顿距离最近的检查点，然后输出即可。
### Code:
-----
```c++
#include<bits/stdc++.h>
#define ll long long
#define un unsigned
#define re register
using namespace std;
inline ll read(){//快读 
	ll x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')y=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*y;
}
inline void wr(ll x){//快输 
	if(x<0) putchar('-'),x=-x;
	if(x>9) wr(x/10);
	putchar(x%10+48);
	return;
}
inline void write(ll x,char y){wr(x),putchar(y);}

int n,m,a[100],b[100],c[100],d[100],ans;
int mhd(int x1,int y1,int x2,int y2){//曼哈顿距离函数 
	return abs(x1-x2)+abs(y1-y2);
}
int main(){  
	n=read(),m=read();
	for(int i=1;i<=n;i++)a[i]=read(),b[i]=read();
	for(int i=1;i<=m;i++)c[i]=read(),d[i]=read();
	for(int i=1;i<=n;i++){//暴力 
		ans=1;
		for(int j=1;j<=m;j++)
			if(mhd(a[i],b[i],c[ans],d[ans])>mhd(a[i],b[i],c[j],d[j]))//找到比ans小的就更新ans 
				ans=j;
		write(ans,'\n');//最后输出 
	}
    return 0;
}
```

---

## 作者：·糯· (赞：0)

## 题目分析
此题因为数据范围较小，所以我们可以直接暴力枚举每个学生与每个检查点，求它们曼哈顿距离的最小值，每找到一个最小值就更新下标，最后输出这个最小值的下标就是该学生应该去的检查点，注意曼哈顿距离应取绝对值，我们可以直接使用自带函数。
## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[60],b[60],c[60],d[60];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>a[i]>>b[i];
	for(int i=1;i<=m;i++)
		cin>>c[i]>>d[i];
	for(int i=1;i<=n;i++){
		int mini=1e9,id=0;
		for(int j=1;j<=m;j++)
			if(abs(a[i]-c[j])+abs(b[i]-d[j])<mini){
				mini=abs(a[i]-c[j])+abs(b[i]-d[j]);//曼哈顿距离
				id=j;//更新下标
			}
		cout<<id<<endl;
	}	
	return 0;
}
```


---

## 作者：CrTsIr400 (赞：0)

我们发现 $n\le 50$ ，于是考虑暴力 $O(nm)$ 算法求解。

思路：枚举每一个学生 $i$ ，再枚举每个检查站 $j$ ，计算他们的距离。

大致流程就如此了。

```cpp
for(i=1,minp;i<=n;++i)//枚举每个学生
{
	for(j=2,minn=DIST(i,1);j<=m;++j)//枚举每个检查站
    	if(DIST(i,j)<minn)
        	minp=j,minn=DIST(i,j);
	printf("%d\n",minp);
}
	
```

`DIST` 函数为计算学生和检查站的距离。

---

## 作者：chengni (赞：0)

说来惭愧，第一反应居然是广搜，但数据范围肯定是GG的，后来发现问的只是去哪个站而已，没说走几步，那循环一波求最小值就可以了。

```cpp
#include<bits/stdc++.h>

using namespace std;

int a[60],b[60],c[60],d[60];


int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i]>>b[i];
	}
	for(int i=1;i<=m;i++)
	{
		cin>>c[i]>>d[i];
	}
	
	for(int i=1;i<=n;i++)
	{
		int ans=1000000000;
		int k;
		for(int j=1;j<=m;j++)
		{
			int t=abs(a[i]-c[j])+abs(b[i]-d[j]);
			if(t<ans){
				ans=t;
				k=j;
			}
		}
		cout<<k<<endl;
	}
	return 0;
} 
```

---

