# The Wedding

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=18&page=show_problem&problem=1603

[PDF](https://uva.onlinejudge.org/external/106/p10662.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10662/ab41e0babb1499da2a267d5f5662f0b7680375d6.png)

## 样例 #1

### 输入

```
2 2 2
12 0 0
1 1 1
34 0 0
3 1 1
21 1 0
2 1 0
2 2 2
12 0 0
1 0 0
34 0 0
3 0 0
21 0 0
2 0 0
5 5 6
970 0 1 1 1 0
856 0 0 0 0 0
1290 1 0 0 1 0
1361 0 0 1 0 0
82 0 0 0 0 1
1182 0 0 0 1 1 0
450 0 1 1 0 0 1
895 0 0 1 0 1 1
1865 0 1 0 0 1 1
183 1 1 1 1 1 0
252 1 1 1 0 1
1813 1 0 0 1 1
1429 0 0 1 0 0
1522 1 1 1 0 0
1762 0 0 1 0 1
1946 0 1 0 0 0```

### 输出

```
Don't get married!
1 1 1:6
4 1 3:2054```

# 题解

## 作者：Malkin_Moonlight (赞：3)

# 题解：UVA10662 The Wedding

~~好久没有写题解了，今天来写一下~~。


题目给你 $t$ 个旅行社，$r$ 个餐厅，$h$ 个酒店的价格以及每个旅行社，餐厅，酒店之间能否搭配。

求一个能使旅行社，餐厅，酒店都可以搭配的方案的最小的总价格。

找不到就输出 `Don't get married!`。

我们可以发现，题目给的 $t，r，h$ $< $ $20$，所以直接暴力枚举可能的方案，就可以找出最小总价格。

时间复杂度 $O(n^3)$。

---

## 作者：Alice2012 (赞：2)

## Solution

算法：枚举。

发现 $T,R,H$ 均在 $20$ 以内，考虑将所有三元组 $(x,y,z)$ 枚举出来，表示第 $x$ 个旅行团，第 $y$ 个餐厅，第 $z$ 个旅馆。若这个三元组合法，则它们的花费可以被统计进最小花费。

同时需要注意本题输入、输出格式。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=25;
int n,m,k,X,Y,Z,ans=1e18;
int a[N][N],b[N][N],c[N][N];
signed main(){
	while(cin>>n>>m>>k){
		for(int i=1;i<=n;i++)
			for(int j=0;j<=m;j++)
				cin>>a[i][j]; 
		for(int i=1;i<=m;i++)
			for(int j=0;j<=k;j++)
				cin>>b[i][j];
		for(int i=1;i<=k;i++)
			for(int j=0;j<=n;j++)
				cin>>c[i][j];
		//a[i][0],b[i][0],c[i][0] 分别表示第 i 个旅行团, 餐厅, 旅馆的价格. 
		for(int x=1;x<=n;x++){
			for(int y=1;y<=m;y++){
				for(int z=1;z<=k;z++){
					if(a[x][y]||b[y][z]||c[z][x])continue;//该三元组 (x,y,z) 不合法, 即 (x,y),(y,z),(z,x) 中存在没有联系的关系.
					if(a[x][0]+b[y][0]+c[z][0]<ans)ans=a[x][0]+b[y][0]+c[z][0],X=x,Y=y,Z=z;//统计最小答案.
				}
			}
		}
		if(ans==1e18)cout<<"Don't get married!\n";
		else printf("%lld %lld %lld:%lld\n",X-1,Y-1,Z-1,ans);//注意题面下标从 0 开始, 所以要 -1. 
		ans=1e18;
	}
	return 0;
}
```

听说赛前写题解可以 rp++，所以祝自己 rp++！

---

## 作者：Speech_less (赞：2)

# UVA10662 The Wedding 
  [题目传送门](https://www.luogu.com.cn/problem/UVA10662)

### PART 1：主要思路
本题看似很复杂，其实输入后直接暴力枚举加排序即可。

------------

### PART 2：输入
大概：由于题目要输入的数为矩形状，所以可以用循环嵌套来完成题目中的输入。切记每组数据必须从第 $0$ 个开始记！！！

下面这个图是用来理解题目的输入的。样例分三组数据，每组都是一个问题，这里我门只讨论第一组。

![](https://cdn.luogu.com.cn/upload/image_hosting/uim16tkn.png?x-oss-process=image/resize,m_lfit,h_1000,w_200)

按照题目的要求来说黄色部分是每组的旅行团 $T$，餐厅 $R$ 和旅馆 $H$ 的数量。

红色部分：共 $T$ 行，$R + 1$ 列。第一列的第 $j$ 行表示的是第 $j$ 家旅行团价格。输入完价格后，第 $i$ 列，第 $j$ 行，的数代表的是第 $i$ 家餐厅和第 $j$ 家旅行团能否联合在一起，$0$ 表示可以，$1$ 表示不行。

绿色部分：共 $R$ 行，$H + 1$ 列。第一列的第 $j$ 行表示的是第 $j$ 家餐厅价格。输入完价格后，第 $i$ 列，第 $j$ 行的数代表的是第 $i$ 家旅馆和第 $j$ 家餐厅能否联合在一起，$0$ 表示可以，$1$ 表示不行。

橙色部分：共 $H$ 行，$T + 1$ 列。第一列的第 $j$ 行表示的是第 $j$ 家旅馆价格。输入完价格后，第 $i$ 列，第 $j$ 行，的数代表的是第 $i$ 家旅行团和第 $j$ 家旅馆能否联合在一起，$0$ 表示可以，$1$ 表示不行。

代码实现：
```cpp
for(int i=0;i<t;i++){	//红色
	cin>>tt[i];			//第一栏是旅行团价的格 
	for(int j=0;j<r;j++){
		cin>>tr[i][j];	//后面是旅行团与餐厅的关系 
	}
}
for(int i=0;i<r;i++){	//绿色
	cin>>rr[i];			//第一栏是餐厅的价格 
	for(int j=0;j<h;j++){
		cin>>rh[i][j];	//后面是餐厅与宾馆的关系 
	}
}
for(int i=0;i<h;i++){	//橙色
	cin>>hh[i];			//第一栏是宾馆的价格 
	for(int j=0;j<t;j++){
		cin>>ht[i][j];	//后面是宾馆与旅行团的关系 
	}
}                   
```
------------

### PART 3：模拟部分
大概内容其实模拟部分很简单，只需要用几个变量来记录最小值，然后打擂台即可，当然你也可以排序来解决。

详细解析：只要扫一遍数组就可以了，扫的时候先判断能否满足题目要求：旅行团，餐厅和旅馆能否联系合在一起，即是否为 $0$。接着判断最小价格总和，然后记录下最小值，最小总和的旅行团，餐厅和宾馆的编号。

代码实现：
```cpp
if(tt[i]+rr[j]+hh[k]<minsum){//记录价格总和的最小值（题目没说，但是要写） 
        minsum=tt[i]+rr[j]+hh[k];//最小总和 
        mint=i;//最小总和的旅行团编号 
	minr=j;//最小总和的餐厅编号 
	minh=k;//最小总和的宾馆编号 
	flag=1;//记录是否有可以联系在一起的旅行团，餐厅，宾馆 
}
```
------------
### PART 4：特判输出
由于题目中有第二种输出情况：没有任何一家旅行团，餐厅和旅馆能联系在一起输出 `Don't get marrid!`。所以，我们要对这种情况进行特判。

我的方法是：用一个 bool 变量来记录模拟部分中，有没有进入过判断语句，如果有，就证明有结果，没有就证明无结果，输出 `Don't get marrid!`。

代码实现：
```cpp
if(flag) printf("%d %d %d:%d\n",mint,minr,minh,minsum);//有，就输出最小总和，最小总和的旅行团，餐厅，宾馆的编号
else cout<<"Don't get married!"<<endl;//没有就输出"Don't get married!"
```
------------

### AC 代码上交：
```cpp
#include<bits/stdc++.h>//万能头 
using namespace std;
bool tr[20][20],rh[20][20],ht[20][20];//后面用来记录T-R/R-H/H-T能否组合在一起 
int main(){
	int t,r,h,tt[25],rr[25],hh[25];//记录价格 
	while(cin>>t>>r>>h){//不定几组 
		bool flag=0;//记录是否满足要求 
		int mint,minr,minh,minsum=0x7f7f7f7f;//记录最小值 
		for(int i=0;i<t;i++){//开始输入          切记！！！接下来的输入必须从第0组开始 
			cin>>tt[i];//第一栏是旅行团价的格 
			for(int j=0;j<r;j++){
				cin>>tr[i][j];//后面是旅行团与餐厅的关系 
			}
		}
		for(int i=0;i<r;i++){
			cin>>rr[i];//第一栏是餐厅的价格 
			for(int j=0;j<h;j++){
				cin>>rh[i][j];//后面是餐厅与宾馆的关系 
			}
		}
		for(int i=0;i<h;i++){
			cin>>hh[i];//第一栏是宾馆的价格 
			for(int j=0;j<t;j++){
				cin>>ht[i][j];//后面是宾馆与旅行团的关系 
			}
		}                    //结束输入 
		for(int i=0;i<t;i++){//枚举每一家旅行团，餐厅，宾馆的情况 
			for(int j=0;j<r;j++){
				for(int k=0;k<h;k++){
					if(tr[i][j]==0&&rh[j][k]==0&&ht[k][i]==0){//如果他们都能组合在一起就考虑判断最小值 
						if(tt[i]+rr[j]+hh[k]<minsum){//记录价格总和的最小值（题目没说，但是要写） 
                   					minsum=tt[i]+rr[j]+hh[k];//最小总和 
                   					mint=i;//最小总和的旅行团编号 
							minr=j;//最小总和的餐厅编号 
							minh=k;//最小总和的宾馆编号 
							flag=1;//记录是否有可以联系在一起的旅行团，餐厅，宾馆 
                        			}
					}
				}
			}
		}
		if(flag) printf("%d %d %d:%d\n",mint,minr,minh,minsum);//有，就输出最小总和，最小总和的旅行团，餐厅，宾馆的编号  
		else cout<<"Don't get married!"<<endl;//没有就输出"Don't get married!"
	}
	return 0;//完美结束 
}
```

------------

#### 感谢@东方澂相助
\*注：切记勿抄袭，抄袭马上变棕名。

题外：我已经改了很多次啦，求管理员大大给过吧 QwQ。

---

## 作者：ZSYZSYZSYZSY (赞：1)

# UVA10662 The Wedding
[R179299513 记录详情](https://www.luogu.com.cn/record/179299513)

## Main Idea
给你 $T$ 个旅行社，$R$ 个餐厅，$H$ 个酒店的价格以及每个旅行社，餐厅，酒店之间能否搭配。

求一个能使旅行社，餐厅，酒店都可以搭配的方案的最小的总价格。

如果有解，输出最小总价格、旅行社、餐厅和酒店的编号；如果无解，则输出 `Don't get married!`。

## Solution
注意到 $T, R, H (T, R, H \leq 20)$，所以考虑 $O(n^3)$ 枚举每种搭配找最小总价格。

注意：本题中允许搭配为 $0$，不允许才是 $1$。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define INF 1e15

inline ll read()
{
	ll x = 0, f = 1;
	char c = getchar();
	while(c < '0' || c > '9')
	{
		if(c == '-')
		{
			f = -1;
		}
		c = getchar();
	}
	while(c >= '0' && c <= '9')
	{
		x = (x << 1) + (x << 3) + c - '0';
		c = getchar();
	}
	return x * f;
}

ll t, r, h;
ll travel[50], restaurant[50], hotel[50];
bool travel_restaurant[50][50];
bool restaurant_hotel[50][50];
bool hotel_travel[50][50];

int main()
{
	while(cin >> t >> r >> h)
	{
		bool flag = 0;
		ll min_travel, min_restaurant, min_hotel, minsum = 0x7f7f7f7f;
		for(ll i = 0; i < t; i++)
		{
			travel[i] = read();
			for(ll j = 0; j < r; j++)
			{
				travel_restaurant[i][j] = read();
			}
		}
		for(ll i = 0; i < r; i++)
		{
			restaurant[i] = read();
			for(ll j = 0; j < h; j++)
			{
				restaurant_hotel[i][j] = read();
			}
		}
		for(ll i = 0; i < h; i++)
		{
			hotel[i] = read();
			for(ll j = 0; j < t; j++)
			{
				hotel_travel[i][j] = read();
			}
		}
		for(ll i = 0; i < t; i++)
		{
			for(ll j = 0; j < r; j++)
			{
				for(ll k = 0; k < h; k++)
				{
					if(travel_restaurant[i][j] == 0 && restaurant_hotel[j][k] == 0 && hotel_travel[k][i] == 0)
					{
						if(minsum > travel[i] + restaurant[j] + hotel[k])
						{
							minsum = travel[i] + restaurant[j] + hotel[k];
							min_travel = i, min_restaurant = j, min_hotel = k;
							flag = 1;
						}
					}
				}
			}
		}
		if(flag)
		{
			printf("%lld %lld %lld:%lld\n", min_travel, min_restaurant, min_hotel, minsum);
		}
		else
		{
			cout << "Don't get married!" << endl;
		}
	}
	return 0;
}
```

---

## 作者：Florrer_A (赞：0)

## 思路
由于这道题的 $T,R,H≤20$ 所以可以用 $O(n^3)$ 的复杂度枚举所有可能的方案数，可以通过本题。

---

## 作者：YangXiaopei (赞：0)

## 题目大意：

给你 $t$ 个旅行社，$r$ 个餐厅，$h$ 个酒店的价格以及每个旅行社，餐厅，酒店之间能否搭配。

求一个能使旅行社，餐厅，酒店都可以搭配的方案的最小的总价格。

找不到输出 `Don't get married!`。

## Solution:

注意到 $t, r, h$ 都很小，只到 $20$，考虑三重循环枚举每种搭配找最小总价格。

注意：本题中允许搭配为 $0$，不允许才是 $1$。

## Code:

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t, r, h, x, y, z, minn, a[25][25], b[25][25], c[25][25];
signed main(){
	while(cin >> t >> r >> h){
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
        memset(c, 0, sizeof(c));
        for(int i = 1; i <= t; i++){
            for(int j = 0; j <= r; j++){
                cin >> a[i][j];//a[i][0] 代表第i个旅行社的价格。
            }
        }
        for(int i = 1; i <= r; i++){
            for(int j = 0; j <= h; j++){
                cin >> b[i][j];//b[i][0] 代表第i个餐厅的价格。
            }
        }
        for(int i = 1; i <= h; i++){
            for(int j = 0; j <= t; j++){
                cin >> c[i][j];//c[i][0] 代表第i个酒店的价格。
            }
        }
        minn = 1e18;
        for(int i = 1; i <= t; i++){
            for(int j = 1; j <= r; j++){
                for(int k = 1; k <= h; k++){
                    if(a[i][j] == 0 && b[j][k] == 0 && c[k][i] == 0){//是否可以搭配
                        if(minn > a[i][0] + b[j][0] + c[k][0]){
                            x = i, y = j, z = k;//记录最小花费对应的旅行社，餐厅，酒店
                        }
                        minn = min(minn, a[i][0] + b[j][0] + c[k][0]);
                    }
                }
            }
        }
        if(minn == 1e18){//无法搭配
            cout << "Don't get married!\n";
        }
        else{
            cout << x - 1 << " " << y - 1 << " " << z - 1 << ":" << minn << "\n";//由于题目中默认编号从0开始，代码中写的则是1开始，所以要减一
        }
    }
	return 0;
}
```

---

## 作者：Chillturtle (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/UVA10662)

# 题意

可见 [这篇帖子](https://www.luogu.com/discuss/398300)，已经翻得很清楚了。

# 思路

这里先大致分析一下：首先，我们有三个不同种类消费的数据，且知道两个不同种类的不同消费源是否能够同时使用。面对 $T < 20,R < 20,H < 20$ 的友好数据，果断选择 $O(T \times R \times H)$ 的优雅暴力。

第一步，进行读入。这里建议将表示两者之间关系的数组名命为 `t_r` 这样形式的。表示 T 与 R 之间的关系。当然 H 与 T，R 与 H 也同理，表示为 `h_t` 和 `r_h`。接下来后面的判断就成功被简化了。

```cpp
for(int i=1;i<=t;i++){
    cin>>T[i];
    for(int j=1;j<=r;j++){
        cin>>t_r[i][j];
    }
}
for(int i=1;i<=r;i++){
    cin>>R[i];
    for(int j=1;j<=h;j++){
        cin>>r_h[i][j];
    }
}
for(int i=1;i<=h;i++){
    cin>>H[i];
    for(int j=1;j<=t;j++){
        cin>>h_t[i][j];
    }
}
```

第二步，就是进行判断了，很好写的三维循环，见下。

```cpp
int minn=INT_MAX/2,minn_t=0,minn_r=0,minn_h=0;
for(int i=1;i<=t;i++){
    for(int j=1;j<=r;j++){
        for(int k=1;k<=h;k++){
            if(T[i]+R[j]+H[k]<minn&&!t_r[i][j]&&!h_t[k][i]&&!r_h[j][k]){
                minn=T[i]+R[j]+H[k];
                minn_t=i-1;
                minn_r=j-1;
                minn_h=k-1;
            }
        }
    }
}
```

这个位置有两个很恶心的坑：

- 首先，这个数组的下标是从0开始的，所以像我一样平时喜欢从1开始的小朋友记得在记录的时候减一捏。

- 其次，它的存关系的数组是值为0是为真捏。

然后，我们考虑无解情况。这个显而易见，就是循环中没有进入判断的即为无解情况。这里我使用打了一个标记就搞定力。

```cpp
int mark=0;
int minn=INT_MAX/2,minn_t=0,minn_r=0,minn_h=0;
for(int i=1;i<=t;i++){
    for(int j=1;j<=r;j++){
        for(int k=1;k<=h;k++){
            if(T[i]+R[j]+H[k]<minn&&!t_r[i][j]&&!h_t[k][i]&&!r_h[j][k]){
                minn=T[i]+R[j]+H[k];
                minn_t=i-1;
                minn_r=j-1;
                minn_h=k-1;
                mark=1;
            }
        }
    }
}
```

最后，把上面所有的整合起来，就可以AC力。

# AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=50;
int t,r,h;
int t_r[N][N],h_t[N][N],r_h[N][N];
int T[N],R[N],H[N];
int main(){
    while(cin>>t>>r>>h){
        for(int i=1;i<=t;i++){
            cin>>T[i];
            for(int j=1;j<=r;j++){
                cin>>t_r[i][j];
            }
        }
        for(int i=1;i<=r;i++){
            cin>>R[i];
            for(int j=1;j<=h;j++){
                cin>>r_h[i][j];
            }
        }
        for(int i=1;i<=h;i++){
            cin>>H[i];
            for(int j=1;j<=t;j++){
                cin>>h_t[i][j];
            }
        }
        int mark=0;
        int minn=INT_MAX/2,minn_t=0,minn_r=0,minn_h=0;
        for(int i=1;i<=t;i++){
            for(int j=1;j<=r;j++){
                for(int k=1;k<=h;k++){
                    if(T[i]+R[j]+H[k]<minn&&!t_r[i][j]&&!h_t[k][i]&&!r_h[j][k]){
                        minn=T[i]+R[j]+H[k];
                        minn_t=i-1;
                        minn_r=j-1;
                        minn_h=k-1;
                        mark=1;
                    }
                }
            }
        }
        if(mark==0){
            cout<<"Don't get married!"<<endl;
        }else{
            cout<<minn_t<<" "<<minn_r<<" "<<minn_h<<":"<<minn<<endl;
        }
    }
return 0;
}
```

---

## 作者：_czy (赞：0)

## 分析
就是有三个目标，完成其中一个有多种方式。

但是有一些方式不能共存，求最小代价。

注意到只有 $20$ 种方式，$n^3$ 枚举即可。

无解输出 `Don't get married!`，下标从 $0$ 开始。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,r,h,T[25],R[25],H[25],k1,k2,k3,m;
bool tr[25][25],rh[25][25],ht[25][25];
int main(){
	ios::sync_with_stdio(0);
	if(!(cin>>t>>r>>h))return 0;
	for(int i=1;i<=t;i++){
		cin>>T[i];
		for(int j=1;j<=r;j++)cin>>tr[i][j];
	}
	for(int i=1;i<=r;i++){
		cin>>R[i];
		for(int j=1;j<=h;j++)cin>>rh[i][j];
	}
	for(int i=1;i<=h;i++){
		cin>>H[i];
		for(int j=1;j<=t;j++)cin>>ht[i][j];
	}
	m=1e9;
	for(int i=1;i<=t;i++){
		for(int j=1;j<=r;j++){
			if(tr[i][j])continue;
			for(int k=1;k<=h;k++){
				if(rh[j][k]||ht[k][i])continue;
				int t=T[i]+R[j]+H[k];
				if(t<m)m=t,k1=i,k2=j,k3=k;
			}
		}
	}
	if(m<1e9)printf("%d %d %d:%d\n",k1-1,k2-1,k3-1,m);
	else printf("Don't get married!\n");
	main();
}
```

---

## 作者：Dream_Stars (赞：0)

## 题目大意：

[戳这里](https://www.luogu.com/discuss/398300)。


## 算法解释：

题目意思是有三个量，一个是旅行社，一个是餐厅，一个是酒店，如果它们可以被组合，那么最后的值为 $0$ 否则就是 $1$，输入的数据则是由一组数值和一个表格组成，表格显示的是 $0$ 与 $1$，代表能否被组合。最后输出能被组合的最小总和，如果**无法**被组合，那么就额外输出即可。

别看这道题数据量那么大，其实上很简单。算法上我们可以用一个**三重暴搜**，暴力枚举，如果发现有可以组合，并且比已有值更小的值则进行更新，若没有，则直接进行下一次循环，一直进行比较，最后输出最小的值即可。

因为题目有**多组**测试数据，所以，我们可以使用一个循环，进行无限读入，如 `while(cin>>t>>r>>h)`。

这样便可以实现不知道多少组数据的输入啦，那我这里也不多废话，直接给大家上一下整个**输入部分**的代码。


```cpp
  while(cin>>t>>r>>h){
	for(int i=1;i<=t;i++){
      cin>>a[i];//数据部分。
	  for(int j=1;j<=r;j++)
		cin>>x[i][j];//这个是输入表格部分。
    }//旅行社。
	for(int i=1;i<=r;i++){
      cin>>b[i];
	  for(int j=1;j<=h;j++)
		cin>>y[i][j];
    }//餐厅。
	for(int i=1;i<=h;i++){
      cin>>c[i];
	  for(int j=1;j<=t;j++)
		cin>>z[i][j];
    }//酒店。
}
```
## 代码展示：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N = 30 , MAX = LONG_LONG_MAX;
ll t , r , h , ans;
ll min_t = MAX , min_r = MAX , min_h = MAX , min_ans = MAX;
ll a[N] , b[N] , c[N];
bool x[N][N] , y[N][N] , z[N][N] , f;
int main(){
  while(cin>>t>>r>>h){//多组测试数据的读入。
	for(int i=1;i<=t;i++){//旅行社。
      cin>>a[i];
	  for(int j=1;j<=r;j++)
		cin>>x[i][j];
    }
	for(int i=1;i<=r;i++){//餐厅。
      cin>>b[i];
	  for(int j=1;j<=h;j++)
		cin>>y[i][j];
    }
	for(int i=1;i<=h;i++){//酒店。
      cin>>c[i];
	  for(int j=1;j<=t;j++)
		cin>>z[i][j];
    }//输入数据。
    f = false , min_t = MAX , min_r = MAX , min_h = MAX , min_ans = MAX;//在暴搜前初始化变量。
    for(int i=1;i<=t;i++)
     for(int j=1;j<=r;j++)
      for(int k=1;k<=h;k++){
	    ans = a[i] + b[j] + c[k];//算出值。
        if(x[i][j] == 0 && y[j][k] == 0 && z[k][i] == 0 && min_ans > ans)//如果可以组合并且值小于我们存入的最小值，那么就更新各项数值。
		  min_t = i - 1 , min_r = j - 1 , min_h = k - 1 , f = true , min_ans = ans;//更新数值。
//这里在更新数值的时候要注意一点，因为我们的循环是从1开始的，而计算是从0开始的，所以，在更新数值时需要减1.
	  }
	if(f == false)
	  cout<<"Don't get married!"<<endl;//如果哨兵f为false，证明没有组合，即输出Don't get married。
	else
	  cout<<min_t<<" "<<min_r<<" "<<min_h<<":"<<min_ans<<endl;//否则就说明肯定有组合，直接输出最小值即可。
  }
  return 0;//return 养成好习惯。
} 
```

---

## 作者：__little__Cabbage__ (赞：0)

## Description

给定 $3$ 个长度分别为 $t,r,h$ 序列 $p_1 , p_2 , p_3$ 表示价格，再给定 $3$ 个大小分别为 $t \times r , r \times h , h \times t$ 的 $01$ 矩阵 $c_1 , c_2 , c_3$ 表示 $c_{k,i,j}$ 表示 $p_{k,i}$ 是否可以与 $p_{k+1 \bmod 3,j}$ 同时选择。求在 $p_1 , p_2 , p_3$ 中都选择一项的最小花费。


## Solution

因为 $t,r,h < 20$，所以考虑 $O(trh)$ 暴力枚举每种可能的选择，每次判断一下当前组合是否合法，然后如果小于当前答案则更新答案即可。

需要注意的是，数组的下标从 $0$ 开始。

## Code

```cpp
#include<iostream>
#include<cstdio>
//#define int long long
using namespace std;

const int MAXN=20+5;
int t,r,h,p1[MAXN],p2[MAXN],p3[MAXN];
int c1[MAXN][MAXN],c2[MAXN][MAXN],c3[MAXN][MAXN];

signed main()
{
    ios::sync_with_stdio(0);
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while(cin>>t>>r>>h)
    {
        for(int i=1;i<=t;++i)
        {
            cin>>p1[i];
            for(int j=1;j<=r;++j) cin>>c1[i][j];
        }
        for(int i=1;i<=r;++i)
        {
            cin>>p2[i];
            for(int j=1;j<=h;++j) cin>>c2[i][j];
        }
        for(int i=1;i<=h;++i)
        {
            cin>>p3[i];
            for(int j=1;j<=t;++j) cin>>c3[i][j];
        }

        int ans=2e9,ai,aj,ak;
        for(int i=1;i<=t;++i)
            for(int j=1;j<=r;++j)
                for(int k=1;k<=h;++k)
                    if(!c1[i][j] && !c2[j][k] && !c3[k][i] && p1[i]+p2[j]+p3[k]<ans)
                        ans=p1[i]+p2[j]+p3[k],ai=i-1,aj=j-1,ak=k-1;

        if(ans==2e9) cout<<"Don't get married!\n";
        else cout<<ai<<' '<<aj<<' '<<ak<<':'<<ans<<'\n';
    }

    return 0;
}

```

---

## 作者：ALANYQ (赞：0)

一道简单的模拟题……

使用三层循环，枚举是否满足条件：旅行社，餐馆，酒店都互相满足。若满足条件，更新答案的值。

若退出循环时，答案的值没有变化，则输出”Don't get married!“

注意：有多组数据！

## CODE:
```cpp
#include <bits/stdc++.h>
using namespace std;
int t,r,h;//存储 T,H,R
int ans,x,y,z;//存储答案，旅行社，餐厅，酒店
int p1[20],p2[20],p3[20];//存储价格
int f1[20][20],f2[20][20],f3[20][20];//存储是否满足
int main()
{
	while (cin >> t >> r >> h)//输入判断
	{
		ans=1e9;//初始化
		for (int i=1;i<=t;i++)
		{
			cin >> p1[i];//输入价格
			for (int j=1;j<=r;j++) cin >> f1[i][j];//输入是否满足
		}
		for (int i=1;i<=r;i++)
		{
			cin >> p2[i];//输入价格
			for (int j=1;j<=h;j++) cin >> f2[i][j];//输入是否满足
		}
		for (int i=1;i<=h;i++)
		{
			cin >> p3[i];//输入价格
			for (int j=1;j<=t;j++) cin >> f3[i][j];//输入是否满足
		}
		for (int i=1;i<=t;i++)//枚举旅行社
		{
			for (int j=1;j<=r;j++)//枚举餐厅
			{
				for (int k=1;k<=h;k++)//枚举酒店
				{
					if (!f1[i][j]&&!f2[j][k]&&!f3[k][i])//如果满足所有条件
					{
						if (p1[i]+p2[j]+p3[k]<ans)//如果小于当前答案
						{
							ans=p1[i]+p2[j]+p3[k],x=i-1,y=j-1,z=k-1;//更新答案
						}
					}
				}
			}
		}
		if (ans!=1e9) cout << x << " " << y << " " << z << ":" << ans << endl;//如果答案的值有被更新，输出答案
		else cout << "Don't get married!\n";//否则输出
	}
	return 0;
}
```

---

