# [GCJ 2008 #1B] Crop Triangles

## 题目描述

一些恶作剧者看了太多的 Discovery Channel，现在他们想在夜晚建造一个“作物三角形”。他们想要在一片看起来像均匀网格的大农田里建造这个三角形。从上方看，农田是一个均匀分布的网格。有一些树被种在田地里，每棵树都位于两条网格线的交点（即网格点）上。恶作剧者希望他们的作物三角形的顶点都位于这些树上。此外，为了让三角形更有趣，他们还希望三角形的中心也位于某个网格点上。我们提醒你，如果一个三角形的顶点分别为 $(x_1, y_1)$、$(x_2, y_2)$ 和 $(x_3, y_3)$，那么该三角形的中心坐标为 $((x_1 + x_2 + x_3) / 3, (y_1 + y_2 + y_3) / 3)$。

你将获得一组整数坐标点，表示所有树在网格上的位置。请你计算，在这些点中可以选出多少个不同的三元组，使得它们组成的三角形的中心也是一个网格点（即中心坐标也是整数）。

如果三角形的面积为 $0$，我们仍然认为它是一个合法的三角形。

## 说明/提示

**样例解释**

在第一个测试用例中，生成的 $4$ 棵树的坐标分别为 $(0, 1)$、$(7, 3)$、$(17, 5)$、$(17, 7)$。

**数据范围**

- $1 \leq N \leq 10$，
- $0 \leq A, B, C, D, x_0, y_0 \leq 10^9$，
- $1 \leq M \leq 10^9$。

**小数据范围（5 分，测试点 1 - 可见）**

- $3 \leq n \leq 100$。

**大数据范围（10 分，测试点 2 - 隐藏）**

- $3 \leq n \leq 100000$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
4 10 7 1 2 0 1 20
6 2 0 2 1 1 2 11```

### 输出

```
Case #1: 1
Case #2: 2```

# 题解

## 作者：jsisonx (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/P13460)

# 题目分析

给定 $n$ 个点，可以从这些点中选出多少个不同三元组使得三个点的横坐标之和为三的倍数，纵坐标值和也为三的倍数。

用数学语言表达上面的话，就是 $x_1+x_2+x_3 \equiv 0 \pmod 3$，$y_1+y_2+y_3 \equiv 0 \pmod 3$。变形得 $x_2+x_3 \equiv -x_1 \pmod 3$，$y_2+y_3 \equiv -y_1 \pmod 3$。

设 $A_i=(x_i,y_i)$，则我们需要找形如 $(A_1,A_2,A_3)$ 的三元组。显然，我们可以枚举所有 $i$ 作为 $A_1$，然后再所有编号小于 $i$ 的点中找 $A_2$ 和 $A_3$（这是为了去重）。由于我们只关心模 $3$ 后的值，因此我们可以把所有点的横纵坐标先模 $3$。此时，每个点的横纵坐标都为 $0$，$1$，$2$ 中的一个。

具体地，对于 $A_i=(x_i,y_i)$，我们要找两个点 $A_j=(x_j,y_j)$ 与 $A_k=(x_k,y_k)$ 使得 $j<i$，$k<i$，且 $(x_j+x_k) \bmod 3=-x_i\bmod 3$，$(y_j+y_k)\bmod 3=-y_i\bmod 3$。由于每个点的横纵坐标都为 $0$，$1$，$2$ 中的一个，所以我们可以用一个二维数组存储编号小于 $i$ 的点中横纵坐标为 $(x,y)$ 的点有多少个，记为 $f_{x,y}$，并设编号小于 $i$ 的点中横纵坐标为 $(x,y)$ 的点的集合为 $s_{x,y}$，我们有 $\left| s_{x,y}\right| =f_{x,y}$。这样，我们可以从 $0$ 到 $2$ 枚举 $x_j$ 和 $y_j$，则 $x_k=(3-x_i-x_j) \bmod 3$，$y_k=(3-y_i-y_j) \bmod 3$。如果 $(x_j,y_j)$ 与 $(x_k,y_k)$ 不完全相同，则 $s_{x_j,y_j}\cap s_{x_k,y_k}$ 为空，此时任意从 $s_{x_j,y_j}$ 与 $s_{x_k,y_k}$ 中各取一个都能满足要求，则方案总数为 $f_{x_j,y_j} \times f_{x_k,y_k}$。如果 $(x_j,y_j)$ 与 $(x_k,y_k)$ 完全相同，则方案数变为 $C_{f_{x_j,y_j}}^2=\frac{f_{x_j,y_j} \times (f_{x_j,y_j}-1)}{2}$。答案即为每一次方案数之和。注意每次算完之后更新 $f$ 数组，注意枚举 $x_j$，$y_j$ 时也要去重，因为可能出现先枚举了 $x_j$，后面又枚举到 $(3-x_i-x_j)\bmod 3$ 的情况，这两次枚举实际上是相同的，只能取一个。

# 代码

```
#include<bits/stdc++.h>
#define N 100001
using namespace std;
int f[3][3],mem[3][3][3][3];
struct tree{
	long long x,y;
}tr[N];
int main(){
	int t;
	cin>>t;
	for(int o=1;o<=t;o++){
		cout<<"Case #"<<o<<": ";
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                f[i][j]=0;
            }
        }
		int n;
		long long a,b,c,d,x0,y0,m,ans=0;
		cin>>n>>a>>b>>c>>d>>x0>>y0>>m;
		long long x1=x0,y1=y0;
		tr[1].x=x1;
		tr[1].y=y1;
		for(int i=2;i<=n;i++){
			x1=(a*x1+b)%m;
			y1=(c*y1+d)%m;
			tr[i].x=x1;
			tr[i].y=y1;
		}
		for(int i=1;i<=n;i++){
			tr[i].x%=3;
			tr[i].y%=3;
		}
		for(int i=1;i<=n;i++){
			int p1=3-tr[i].x,p2=3-tr[i].y;
            for(int h=0;h<3;h++){
                for(int r=0;r<3;r++){
                    for(int v=0;v<3;v++){
                        for(int u=0;u<3;u++){
                            mem[h][r][v][u]=0;
                        }
                    }
                }
            }
			for(int j=0;j<3;j++){
				for(int k=0;k<3;k++){
					int j1=j,j2=p1-j,k1=k,k2=p2-k;
                    if(j2==3){
                        j2=0;
                    }
                    if(k2==3){
                        k2=0;
                    }
                    if(j1==3){
                        j1=0;
                    }
                    if(k1==3){
                        k1=0;
                    }
                    if(j2<0){
                        j2+=3;
                    }
                    if(k2<0){
                        k2+=3;
                    }
					if(j1==j2&&k1==k2){
						if(mem[j1][k1][j2][k2]==0){
                            ans+=(f[j1][k1]*(f[j1][k1]-1))/2;
                            mem[j1][k1][j2][k2]=1;
                        }
					}
					else{
                        if(mem[j1][k1][j2][k2]==0&&mem[j2][k2][j1][k1]==0){
    						ans+=f[j1][k1]*f[j2][k2];
                            mem[j1][k1][j2][k2]=1;//去重
                        }
					}
				}
			}
			f[tr[i].x][tr[i].y]++;//更新f数组
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：__coderyc__ (赞：4)

## 思路
[烤鸡](https://www.luogu.com.cn/problem/P2089)既视感。

对于每一个可能的点的三元组进行枚举，如果符合题目中这三个点行坐标和与列坐标和除以三都是整数，计入答案，不就六层循环而已。

这里有个小技巧，如果除以三是整数，说明这个数除以三的余数是零，不必硬要算出这个数除完是几。

注意题目中提到的生成树坐标的方式及 GCJ 标准格式化输出就行啦。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    for (int c = 1; c <= N; ++c) {
        int n, A, B, C, D, x0, y0, M;
        cin >> n >> A >> B >> C >> D >> x0 >> y0 >> M;
        int cnt[3][3] = {0};
        long long X = x0, Y = y0;
        cnt[X % 3][Y % 3]++;
        //数据生成器
        for (int i = 1; i < n; ++i) {
            X = (A * X + B) % M;
            Y = (C * Y + D) % M;
            cnt[X % 3][Y % 3]++;
        }
        long long ans = 0;  //十年OI一场空，_______
        for (int a = 0; a < 3; ++a) {  //第一点x
            for (int b = 0; b < 3; ++b) { //第一点y
                for (int c = 0; c < 3; ++c) { //第二点x
                    for (int d = 0; d < 3; ++d) {
                        for (int e = 0; e < 3; ++e) { //第二点y，后面就是第三个点的x和y
                            for (int f = 0; f < 3; ++f) {
                                if ((a + c + e) % 3 == 0 && (b + d + f) % 3 == 0) {
                                    long long cnt1 = cnt[a][b];
                                    long long cnt2 = cnt[c][d];
                                    long long cnt3 = cnt[e][f];
                                    if (a == c && b == d) cnt2--;
                                    if (a == e && b == f) cnt3--;
                                    if (c == e && d == f) cnt3--;
                                    if (cnt1 > 0 && cnt2 > 0 && cnt3 > 0) {
                                        ans += cnt1 * cnt2 * cnt3;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        ans /= 6; 
        cout << "Case #" << c << ": " << ans << endl; //格式化输出
    }
    return 0;
}
```

![目前最优解](https://cdn.luogu.com.cn/upload/image_hosting/7om4xm4x.png)
抢个最优解。

---

## 作者：_ACGODs_ (赞：4)

# P13460 题解
本题解使用了 2025 年 7 月渲染更新以优化视觉效果。
## 思路
容易发现，三角形的三个点的 $x$ 坐标之和和 $y$ 坐标之和都要为 $3$ 的倍数时，中心点才能满足条件。  
也就是：  
$$ x_0+x_1+x_2 \equiv 0 \pmod 3 $$
:::align{center}
且
:::
$$ y_0+y_1+y_2 \equiv 0 \pmod 3 $$
下文中“条件”均指以上同余条件。  
我们只需要枚举三个点，满足条件就好了。  
吗？

## 代码优化
枚举的思路是正确的，但效率太低，只能通过小数据集。  
可以发现，每个点可以分为 $9$ 类，分别对应 $x_i ,y_i \bmod 3$ 的那些情况。  
最后，只需要把满足条件的情况组合（也就是这些情况的 $x$ 值和 $y$ 值之和 $\equiv 0 \pmod 3$）乘在一起，再去个重，就好了。  

自认为不清楚的地方，请配合代码进行理解。
:::info[小优化]
可以先枚举前两个点的 $x ,y \bmod 3$ 的值 ，第三个点可以通过公式求出而不是枚举再判断。  
本题解代码不使用这个优化。
:::  
## 代码
```cpp
//注释会引用思路和优化部分的内容。
#include <bits/stdc++.h>
using namespace std;
//初音未来和多人保持暧昧，我就是受害者之一[doge]
#define int long long
int t, n, a, b, c, d, x[100010], y[100010], m;
int xymd[5][5];
signed main() {
	cin >> t;
	for (int cas = 1; cas <= t; cas++) {
		int ans = 0;
		cin >> n >> a >> b >> c >> d >> x[1] >> y[1] >> m;
		memset(xymd, 0x00, sizeof xymd);//咱班有个同学叫hao*****uo，他没初始化而在去年CSP-T2中获得30分の好成绩。
		xymd[x[1] % 3][y[1] % 3]++;//可以发现，每个点可以分为 9 类，分别对应 xi,yi mod 3 那些情况
		for (int i = 2; i <= n; i++) {
			x[i] = (a * x[i - 1] + b) % m;
			y[i] = (c * y[i - 1] + d) % m;
			xymd[x[i] % 3][y[i] % 3]++;//同上
		}
		ans = 0;
		for (int i = 0; i <= 2; i++) {
			for (int j = 0; j <= 2; j++) {
				for (int k = 0; k <= 2; k++) {
					for (int l = 0; l <= 2; l++) {
						for (int p = 0; p <= 2; p++) {
							for (int q = 0; q <= 2; q++) {
								//枚举情况
								if ((i + k + p) % 3 == 0 && (j + l + q) % 3 == 0) {//最后，只需要把满足条件的情况组合乘在一起
									int cnt1 = xymd[i][j];
									int cnt2 = xymd[k][l];
									int cnt3 = xymd[p][q];
									//不要直接在变量上面减。要么这三个变量作备份，要么这三个变量用来减。
									if (i == k && j == l) cnt2--;
									if (i == p && j == q) cnt3--;
									if (k == p && l == q) cnt3--;
									//再去个重：
									//判断重复的情况。
									//先来后到，后面重复当然去后面的（当然全都去前面的也可以，但是不能一下去前面一下去后面）
									if (cnt1 > 0 && cnt2 > 0 && cnt3 > 0) ans += cnt1 * cnt2 * cnt3;
									//防止负数。如果去重去出负数来了那么说明本来就没有那么多可去。
								}
							}
						}
					}
				}
			}
		}
		cout << "Case #" << cas << ": " << ans / 6 /*还是有重复的，例如 A B C 和 C B A 是一种东西，而被算了两(六)次。*/<< endl;
	}
	return 0;
}
```
$\mathbb{BYE BYE}$

---

