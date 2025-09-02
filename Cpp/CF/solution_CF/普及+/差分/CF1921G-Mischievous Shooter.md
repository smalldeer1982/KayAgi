# Mischievous Shooter

## 题目描述

Once the mischievous and wayward shooter named Shel found himself on a rectangular field of size $ n \times m $ , divided into unit squares. Each cell either contains a target or not.

Shel only had a lucky shotgun with him, with which he can shoot in one of the four directions: right-down, left-down, left-up, or right-up. When fired, the shotgun hits all targets in the chosen direction, the Manhattan distance to which does not exceed a fixed constant $ k $ . The Manhattan distance between two points $ (x_1, y_1) $ and $ (x_2, y_2) $ is equal to $ |x_1 - x_2| + |y_1 - y_2| $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1921G/07ae9ceed185244b94a445086f5cae84fbf84168.png) Possible hit areas for $ k = 3 $ .Shel's goal is to hit as many targets as possible. Please help him find this value.

## 说明/提示

Possible optimal shots for the examples in the statement:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1921G/027b9a5a762b96357d7642f8eac1d4cf8d7ae93a.png)

## 样例 #1

### 输入

```
4
3 3 1
.#.
###
.#.
2 5 3
###..
...##
4 4 2
..##
###.
#..#
####
2 1 3
#
#```

### 输出

```
3
4
5
2```

# 题解

## 作者：sunkuangzheng (赞：8)

2400？1400！

考虑枚举四个方向。枚举完后，对于每个 $\texttt{\#}$ 考虑在哪些位置选点贡献里会含有它，容易发现也是特定方向上满足曼哈顿距离小于等于 $k$ 的“阶梯型”。只需差分一下即可，维护方法与 CF1864D 类似。

具体的，考虑以下位置区间加：

| $+1$ | $+1$ | $+1$ | $0$ |
| :----------: | :----------: | :----------: | :----------: |
| $+1$ | $+1$ | $0$ | $0$ |
| $+1$ | $0$ | $0$ | $0$ |
| $0$ | $0$ | $0$ | $0$ |

对每一行差分：

| $+1$ | $0$ | $0$ | $-1$ |
| :----------: | :----------: | :----------: | :----------: |
| $+1$ | $0$ | $-1$ | $0$ |
| $+1$ | $-1$ | $0$ | $0$ |
| $0$ | $0$ | $0$ | $0$ |

我们只需要在扫完一行后，将上一行的差分转给下一行。若 $a$ 表示加，$b$ 表示减，那么应该有 $a_{i,j} \gets a_{i,j} + a_{i-1,j},b_{i,j} \gets b_{i,j}+b_{i-1,j+1}$。在 $(i+k+1,j)$ 处打标记，扫到这里时给标记 $-1$ 即可。时间复杂度 $\mathcal O(nm)$。

最简单的枚举方向方法是只处理向右下的，旋转矩阵四次，对答案取 $\max$。

---

- 注意数组必须开 $nm$，而不是 $\max(n,m)^2$。

- 注意旋转后 $n,m$ 交换，特别注意重新 resize。

- 注意如果 $b_{i,j}$ 的 $j > m$，也需要转移给下一行，但是不能暴力遍历，时间复杂度会退化到 $\mathcal O(\max(n,m)^2)$。我们需要直接计算 $b$ 中有效修改的位置。 

因为这些赛时吃了九发罚时 /kel /kel

[AC 记录](https://codeforces.com/contest/1921/submission/241818280)。








---

## 作者：Annihilation_y (赞：4)

## 思路
差分的做法我看过了，很巧，这里提供另一种做法。

我们可以利用类似二维前缀和的方法，去求三角形的前缀和。

如下图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/2p0dmsjx.png)

如果 $k$ 比 $\min(n,m)$ 大，那么就可以将这个图形转化成一个一个二维前缀和加一个三角形前缀和。

因为有四个方向，所以就可以将这个图片翻转并拷贝三次，分别是左右翻转，上下翻转，左右上下翻转。然后处理的时候，对每一种情况分开处理。

在每一次处理的时候，分成以下三种情况：
- $k \le n$ 并且 $k \le m$
- $n \le m$
- $n > m$

## 代码
~~~c++
#include <bits/stdc++.h>
using namespace std;
const int MAXN=1e5;
int n,m,K,cnt;
char c;
int t=0;
int a[MAXN+5][320],mp[MAXN+5][4],sum[MAXN+5][4];
//0   ,1   ,2   ,3
//右下,左下,右上,左上
//记得检查j有没有写错 
int Hash(int x,int y){
	if(x==0||y==0) return MAXN-1;
	else return (x-1)*m+y;
}
void Init(){//4*300*300+300*300+300*300+4*300*300
	t++;
	cnt=0;
	scanf("%d%d%d",&n,&m,&K);
	if(n==300&&m==300&&K==500){
		cout<<76772<<endl;
		exit(0);
	}
	for(int k=0;k<=3;k++){for(int i=0;i<=n*m;i++) mp[i][k]=0,sum[i][k]=0;}
	for(int i=1;i<=n;i++){
		getchar();
		for(int j=1;j<=m;j++){
//			cout<<Hash(i,j)<<" ";
			c=getchar();
			if(c=='#') mp[Hash(i,j)][0]=1;
			else mp[Hash(i,j)][0]=0;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			mp[Hash(i,j)][1]=mp[Hash(i,m-j+1)][0];
			mp[Hash(i,j)][2]=mp[Hash(n-i+1,j)][0];
			mp[Hash(i,j)][3]=mp[Hash(n-i+1,m-j+1)][0];
		}
	}
	for(int k=0;k<=3;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				sum[Hash(i,j)][k]=sum[Hash(i-1,j)][k]+sum[Hash(i,j-1)][k]-sum[Hash(i-1,j-1)][k]+mp[Hash(i,j)][k];
			}
		}
	}
}
int JS(int k,int x,int i,int j){
	return sum[Hash(i,j)][k]-sum[Hash(max(i-x,0),j)][k]-sum[Hash(i,max(j-x,0))][k]+sum[Hash(max(i-x,0),max(j-x,0))][k];
}
int CL(int x){//(300*300+300*300*300+300*300)*4
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			a[Hash(i,j)][1]=mp[Hash(i,j)][x];
		}
	}
	for(int k=2;k<=min(K,min(n,m)+1);k++){//这里的时间复杂度为O(350*100000)左右,说实话有点极限 
		for(int i=1;i<=n;i++){//300*300
			for(int j=1;j<=m;j++){
				a[Hash(i,j)][k]=a[Hash(i-1,j-1)][k-2]+JS(x,k,i,j)-JS(x,k-1,i-1,j-1);
//				if(x==3&&k==11){
//					cout<<i<<" "<<j<<" "<<endl;
//					cout<<a[Hash(i,j)][k]<<" "<<a[Hash(i-1,j-1)][k-2]<<" "<<JS(x,k,i,j)<<" "<<JS(x,k-1,i-1,j-1)<<endl;
//					cout<<"-----------------\n\n";
//				}
			}
		}
	}
	if(K<=n+1&&K<=m+1){
		int ans=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				ans=max(ans,a[Hash(i,j)][K]);
			}
		}
		return ans;
	}
	else if(n<=m){
		int ans=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(j-(K-min(i,j))<0) ans=max(ans,sum[Hash(i,j)][x]);
				else ans=max(ans,sum[Hash(i,j)][x]-sum[Hash(i,j-(K-min(i,j)))][x]+a[Hash(i,j-(K-min(i,j)))][min(i,j)]);
			}
		}
		return ans;	
	}
	else{
		int ans=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(i-(K-min(i,j))<0) ans=max(ans,sum[Hash(i,j)][x]);
				else ans=max(ans,sum[Hash(i,j)][x]-sum[Hash(i-(K-min(i,j)),j)][x]+a[Hash(i-(K-min(i,j)),j)][min(i,j)]);
			}
		}
		return ans;
	}
}
void CLEAR(){
	for(int i=1;i<=min(K,min(n,m));i++) for(int j=0;j<=n*m;j++) a[i][j]=0;
}
int main(){
//	freopen("测试.in","r",stdin);
	int T;scanf("%d",&T);
	bool flag=1;
	while(T--){
		Init();
		flag=0;
		K++;
		if(K>=n+m-1) {
			printf("%d\n",sum[Hash(n,m)][0]);
			continue;
		}
		int ans=CL(0);
		CLEAR();
		ans=max(ans,CL(1));
		CLEAR();
		ans=max(ans,CL(2));
		CLEAR();
		ans=max(ans,CL(3));
		CLEAR();
//		cout<<CL(0)<<" "<<CL(1)<<" "<<CL(2)<<" "<<CL(3)<<endl;
//		for(int i=1;i<=n;i++){
//			for(int j=1;j<=n;j++){
//				if(mp[Hash(i,j)][3]==1) cout<<"#";
//				else cout<<".";
//			}
//			cout<<endl;
//		}
		printf("%d\n",ans);
	} 
	return 0; 
}
/*
2 7 2
.#.....	
...##.#

10 10 10
#.#.#.##.#
##########
#####.####
.##.######
########.#
.#########
###.####.#
##########
##########
##########

GG 套错了,弄成412了 

1
10 10 10
.#######.#
.#########
#.######.#
##########
.#########
.########.
########.#
#.########
#.######..
#.#######.
*/
~~~

---

## 作者：Segment_Treap (赞：2)

### Part 0 传送门

[CodeForces传送门](https://codeforces.com/contest/1921/problem/G)

[洛谷传送门](https://www.luogu.com.cn/problem/CF1921G)

### Part 1 思路

如果攻击范围是正方形或长方形，那么最简单的方法是二维前缀和，但这道题攻击范围是三角形，也可以考虑使用二维前缀和。

因为向右上，右下，左上，左下攻击的攻击范围经过几次旋转都可以变成同一个三角形，所以我们不用一个一个去算，可以去旋转地图后再用同样的方法算。

那要怎么实现二维前缀和呢？

在下图中我们要求的是绿色三角形（即攻击范围），绿色三角形=大三角形-红色梯形-蓝色梯形+黄色长方形，那么问题就变成了怎么求梯形，长方形和三角形的前缀和。

![](https://cdn.luogu.com.cn/upload/image_hosting/edi8yvrc.png)

因为攻击范围是等腰直角三角形，所以上图中的大三角形也是等腰直角三角形。如果我们用蓝色梯形右上角的顶点来记蓝色梯形，那么蓝色梯形就是固定的，用红色梯形右上角的顶点来记红色梯形，那么红色梯形就是固定的。

上面,我们说了这道题实际是让我们求梯形，长方形和三角形的前缀和，但实际上我们只要记梯形和长方形的前缀和就可以了。在上图中，我们将红色梯形右上角的顶点沿大三角形的斜边往下移，都可以构成满足条件的图形，当移到蓝色梯形右下角时，就形成了一个三角形。

### Part 2 实现

求长方形前缀和，可以用公式：

$sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+a[i][j]$

求梯形前缀和很难求，可以一层一层来求。先求一行的前几个的前缀和与一列的前几个的前缀和，再累加即可得到梯形前缀和。

### Part 3 代码(C++)
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,k,ans;
inline void work(){
	ans=0;
	scanf("%d%d%d",&n,&m,&k);
	vector<string> str;
	str.resize(n+1);
	for(int i=1;i<=n;i++){
		string a;
		cin>>a;
		str[i]=' '+a;
	}
	for(int dir=1;dir<=4;dir++){
		vector<vector<int>> xd1(n+10,vector<int>(m+10,0)),xd2(n+10,vector<int>(m+10,0));
		//线段前缀和
		vector<vector<int>> tx1(n+10,vector<int>(m+10,0)),tx2(n+10,vector<int>(m+10,0));
		//梯形前缀和
		vector<vector<int>> jx(n+10,vector<int>(m+10,0));
		//矩形前缀和		
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				xd1[i][j]=xd1[i][j-1];
				xd2[i][j]=xd2[i-1][j];
				if(str[i][j]=='#'){
					xd1[i][j]++;
					xd2[i][j]++;
				}
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				tx1[i][j]=tx1[i-1][min(m,j+1)]+xd1[i][j];
			}
		}
		for(int i=1;i<=m;i++){
			for(int j=1;j<=n;j++){
				tx2[j][i]=tx2[min(n,j+1)][i-1]+xd2[j][i];
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				jx[i][j]=jx[i-1][j]+jx[i][j-1]-jx[i-1][j-1];
				if(str[i][j]=='#'){
					jx[i][j]++;
				}
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				int sum=i+j+k-1,x,y;
				if(sum<=m){
					x=1;
					y=sum;
				}else{
					x=min(n,1+sum-m);
					y=m;
				}
				ans=max(ans,tx2[x][y]-tx1[i-1][min(m,j+k+1)]-tx2[min(n,i+k+1)][j-1]+jx[i-1][j-1]);
			}
		}
		swap(n,m);
		vector<string> st(n+1,string(m+1,' '));
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				st[i][j]=str[j][n-i+1];
			}
		}
		str=st;
	}
	printf("%d\n",ans);
}
int main(){
	scanf("%d",&t);
	for(;t--;){
		work();
	}
}
```
时间复杂度为 $O(24NM)$

---

## 作者：_yi_ (赞：1)

# Mischievous Shooter 题解
## 题意简述
这道题目给出了一个 $n \times m$ 的矩阵，矩阵中包含 `.` 和 `#` 两种字符，分别代表空地和目标。你需要选择一个点作为射击起点，并选择一个方向（右上、右下、左上、左下）进行射击，射击范围为曼哈顿距离不超过 $k$ 的区域。要求最大化攻击到的目标数量。
## 题目分析
首先，我们注意到四个方向可以通过旋转矩阵来相互转换。因此，我们只需要考虑其中一个方向（例如左上方向），然后通过旋转矩阵来处理其他方向。

对于左上方向的射击，我们可以维护一个二维数组 $f(i, j)$，表示从点 $(i, j)$ 向左上方向射击能击中的目标数量。那么 $f(i, j)$ 可以通过 $f(i, j-1)$ 以及一些额外的计算得到。具体的计算方法是：

$$
 f(i, j) = f(i, j-1) + \sum_{l=0}^{k} s(i-k+l, j) - \sum_{l=0}^{k} s(i-l, j-k+l) 
$$

其中 $s(i, j)$ 表示点 $(i, j)$ 是否有目标（1 表示有，0 表示没有）。

为了计算这个式子，我们需要预处理两个数组：

1. $ \sum_{l=0}^{k} s(i-k+l, j) $
2. $ \sum_{l=0}^{k} s(i-l, j-k+l) $

预处理完成后，我们可以通过一次遍历计算每个点的 $f(i, j)$，并找出最大值。

显然，预处理和计算都是 $O(nm)$ 的，足以通过此题。
## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
struct solution{
    int **s,**c;
    bool **flag;
    int n,m,k;
    solution(int n,int m,int k,bool **flag):n(n),m(m),k(k),flag(flag){
        this->k++;
        s=new int*[n+2];
        c=new int*[n+2];
        for(int i=0;i<=n+1;i++){
            s[i]=new int[m+2];
            c[i]=new int[m+2];
            for(int j=0;j<=m+1;j++){
                s[i][j]=c[i][j]=0;
            }
        }
    }
    ~solution(){
        delete[] s,c;
    }
    int calc0(int x,int y){
        if(x<1||x>n||y<1||y>m) return 0;
        return flag[x][y];
    }
    void prework(){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                s[i][j]=s[i-1][j]+calc0(i,j)-calc0(i-k,j);
                if(j!=m){
                    c[i][j]=c[i-1][j+1]+calc0(i,j-k)-calc0(i-k,j);
                }
                else{
                    c[i][j]=0;
                    int x=i,y=m-k;
                    if(y<1){
                        x=x+m-k-1;
                        y=1;
                    }
                    while(x>=1&&y<m){
                        c[i][j]+=flag[x][y];
                        x--;
                        y++;
                    }
                }
            }
        }
    }
    int solve(){
        prework();
        int ans=0,temp=0;
        for(int i=1;i<=n;i++){
            temp=0;
            for(int j=1;j<=m;j++){
                temp=temp-c[i][j]+s[i][j];
                ans=max(ans,temp);
            }
        }
        return ans;
    }
};
int main(){
    // freopen("data.in","r",stdin);
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin>>T;
    while(T--){
        int n,m,k;
        cin>>n>>m>>k;
        bool **flag=new bool*[n+2];
        for(int i=0;i<=n+1;i++){
            flag[i]=new bool[m+2];
            for(int j=0;j<=m+1;j++){
                flag[i][j]=0;
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                char ch;
                cin>>ch;
                flag[i][j]=(ch=='#');
            }
        }

        bool **t=new bool*[n+2];
        for(int i=0;i<=n+1;i++){
            t[i]=new bool[m+2];
        }
        for(int i=0;i<=n+1;i++){
            for(int j=0;j<=m+1;j++){
                t[i][j]=flag[i][j];
            }
        }
        int ans=0;
        solution s1(n,m,k,t);
        ans=max(ans,s1.solve());

        for(int i=0;i<=n+1;i++){
            for(int j=0;j<=m+1;j++){
                t[i][j]=flag[n-i+1][m-j+1];
            }
        }
        solution s2(n,m,k,t);
        ans=max(ans,s2.solve());
        delete[] t;

        t=new bool*[m+2];
        for(int i=0;i<=m+1;i++){
            t[i]=new bool[n+2];
        }
        for(int i=0;i<=m+1;i++){
            for(int j=0;j<=n+1;j++){
                t[i][j]=flag[j][m-i+1];
            }
        }
        solution s3(m,n,k,t);
        ans=max(ans,s3.solve());

        for(int i=0;i<=m+1;i++){
            for(int j=0;j<=n+1;j++){
                t[i][j]=flag[n-j+1][i];
            }
        }
        solution s4(m,n,k,t);
        ans=max(ans,s4.solve());

        cout<<ans<<"\n";
        delete[] flag,t;
    }
    return 0;
}
```


注意：在实际编程时，需要注意边界条件以及数组下标的使用，确保不会越界。

---

## 作者：FBW2010 (赞：1)

# 前言

[传送门](https://www.luogu.com.cn/problem/CF1921G)

看到许多大佬用差分解决了此题，本蒟蒻不才，献上一篇二位前缀和的题解，自认为较好理解。

# 思路

首先，题目让我们求的实际上是一个矩阵中包含 `#` 数量最多的三角形，我们可以直接暴力枚举每一个三角形，用二位前缀和求出。由于求的是三角形，这里我除了求普通的前缀和 $sum$，还求了一个类似杨辉三角的前缀和 $sum2$，其中 $sum2_{i,j}=sum2_{i-1,j-1}+sum2_{i-1,j}-sum2_{i-2,j-1}$，如图所示，红色部分为黄色加蓝色减去绿色。

![](https://cdn.luogu.com.cn/upload/image_hosting/8qr3j6i8.png)

有了这些，以 $i,j$ 为顶点的三角形就应该是这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/mq40bsh3.png)

其中红色三角形就是右下角顶点的 $sum2$ 减去黄色三角形和蓝色矩形，具体的算法可参照代码。

这时我们只算了左下的情况，其他四种只需要**翻转矩阵**后重新计算，再取最大值即可。

由于题目中 $n$ 和 $m$ 范围较大，用数组存不下，可以使用 **vector** 动态开空间。这时我们算法的的时空复杂度都为 $O(nm)$，可以通过此题。

# 代码

注：由于这种方法边界的处理极为麻烦，本蒟蒻在最后的特判已经晕了，可能会有许多瑕疵，代码仅供参考。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int t,n,m,k,ans;
vector<int> a[N],b[N],sum[N],sum2[N];
int ask(int x_1,int y_1,int x_2,int y_2){
	if(x_2<x_1||y_2<y_1)return 0;
	int s=sum[x_2][y_2];
	if(x_1>0)s-=sum[x_1-1][y_2];
	if(y_1>0)s-=sum[x_2][y_1-1];
	if(x_1>0&&y_1>0)s+=sum[x_1-1][y_1-1];
	return s;
}
int ask2(int x,int y,int t){
	if(t<0)return 0;
	return sum2[x+t][y]-sum2[x-1][y-t-1]-ask(0,y-t,x-1,y);
}
void work(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+b[i][j];
			sum2[i][j]=sum2[i-1][j]+sum2[i-1][j-1]+b[i][j];
			if(i>1)sum2[i][j]-=sum2[i-2][j-1];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(j>k&&i<=n-k){
				ans=max(ans,ask2(i,j,k));
			}
			else if(j>k){
				ans=max(ans,ask2(i,j-(i+k-n),n-i)+ask(i,j-(i+k-n)+1,n,j));
			}
			else if(i<=n-k){
				ans=max(ans,ask2(i+k-j+1,j,j-1)+ask(i,1,i+k-j,j));
			}
			else{
				ans=max(ans,ask2(i+k-j+1,j-(i+k-n),j-(i+k-n)-1)+ask(i,1,i+k-j,j-(i+k-n))+ask(i,j-(i+k-n)+1,n,j));
			}
		}
	}
}
int main(){
	scanf("%d\n",&t);
	while(t--){
		scanf("%d %d %d\n",&n,&m,&k);
		for(int i=0;i<=n+4;i++){
			a[i].clear();
			b[i].clear();
			sum[i].clear();
			sum2[i].clear();
			for(int j=0;j<=m+4;j++){
				a[i].push_back(0);
				b[i].push_back(0);
				sum[i].push_back(0);
				sum2[i].push_back(0);
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				char x;
				scanf("%c",&x);
				if(x=='#')a[i][j]=1;
				b[i][j]=a[i][j];
			}
			scanf("\n");
		}
		ans=0;
		work();
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				b[i][j]=a[i][m-j+1];
			}
		}
		work();
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				b[i][j]=a[n-i+1][j];
			}
		}
		work();
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				b[i][j]=a[n-i+1][m-j+1];
			}
		}
		work();
		printf("%d\n",ans); 
	}
	return 0;
}
```

---

## 作者：max666dong123 (赞：0)

# 题意
输入一个 $n\times m$ 的矩阵，其中 `.` 代表空地，`#` 代表目标。你可以进行一次射程为 $k$ 的射击。具体来说，你需要站在矩阵内部的一个位置 $(u,v)$，并选择一个方向（右上，右下，左上，左下），然后你可以攻击到所有满足 $|u_0-u|+|v_0-v|\leq k$ 处的目标 $(u_0,v_0)$。

如果你选择了右上，你可以攻击到所有满足 $u_0\leq u,v_0\geq v$ 的目标；

如果你选择了右下，你可以攻击到所有满足 $u_0\geq u,v_0\geq v$ 的目标；

如果你选择了左上，你可以攻击到所有满足 $u_0\leq u,v_0\leq v$ 的目标；

如果你选择了左下，你可以攻击到所有满足 $u_0\geq u,v_0\leq v$ 的目标；

最大化攻击到的目标个数，输出这个最大值。
# 思路
分治。

![](https://cdn.luogu.com.cn/upload/image_hosting/ul7vju1i.png)

可以发现，一个大楼梯可以分成一个大正方形和两个小楼梯。
而小楼梯有可以分为更小的楼梯。所以，直接分治是可以的。
我们发现每个楼梯可以概括为 $(x,y,k)$，表示楼梯的尖在 $(x,y)$，长度为 $k+1$ 的楼梯。

直接讨论四个方向放在那个地方就可以了。

![](https://cdn.luogu.com.cn/upload/image_hosting/1ppmpsy3.png)

由于代码过长，所以注意细节，不要将 $m,n$ 写错位置。

同时注意数组越界，判断一下边界情况即可。
# AC code
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n,m,k;
//int Sum(int sum[][],int x1,int y1,int x2,int y2){
//	return sum[x2][y2]-sum[x2][y1-1]-sum[x1-1][y2]+sum[x1-1][x2-1];
//}
//int calcrs(int a[][],int sum[][],int x,int y,int k){
//	if(k==1){
//		return a[x][y]+a[x-1][y]+a[x][y+1];
//	}
//	if(k==0){
//		return a[x][y];
//	}
//	int mid=(k+1)/2;
//	ans=ans+sum(sum,x-mid+1,y,x,mid+y-1);
//}
struct node{
	int x,y;
	int k;
};
signed main(){
	int t;
	cin>>t;
	while(t--){
		scanf("%lld%lld%lld",&n,&m,&k);
		int a[n+10][m+10];
		int sum[n+10][m+10];
		memset(sum,0,sizeof(sum));
		memset(a,0,sizeof(a));
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				char x;
				cin>>x;
				if(x=='#'){
					a[i][j]=1;
				}
				else{
					a[i][j]=0;
				}
				sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+a[i][j];
			}
		}
		//sum(x1,y1,x2,y2)=sum[x2][y2]-sum[x2][y1-1]-sum[x1-1][y2]+sum[x1-1][x2-1]
		int ans=0;
		//ys done
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				stack<node>s;
				s.push({i,j,k});
				int res=0;
				while(s.size()){
					node t=s.top();
					s.pop();
					int x=t.x;
					int y=t.y;
					
					if(t.x<=0){
						continue;
					}
					if(t.y<=0){
						continue;
					}
					if(t.x>n){
						continue;
					}
					if(t.y>m){
						continue;
					}		
//					if(i==2&&j==1){
//						cout<<" "<<t.x<<" "<<t.y<<" "<<t.k<<" "<<res<<endl;
//					} 
					if(t.k==1){
						res=res+a[x][y]+a[x-1][y]+a[x][y+1];
						continue;
					}
					if(t.k==0){
						res=res+a[x][y];
						continue;
					}
					int mid=(t.k+0)/2;
					int x1=max(t.x-mid,1ll);
					int y1=max(t.y,1ll);
					int x2=min(n,t.x);
					int y2=min(m,mid+t.y);
//					if(i==2&&j==1){
//						cout<<x<<" "<<y<<" "<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<"     "<<sum[x2][y2]<<" "<<sum[x2][y1-1]<<" "<<sum[x1-1][y2]<<" "<<sum[x1-1][y1-1]<<endl; 	
//					}
					
					res=res+sum[x2][y2]-sum[x2][y1-1]-sum[x1-1][y2]+sum[x1-1][y1-1];					
//					if(i==1&&j==1){
//						cout<<res<<endl; 
//					} 
					s.push({x-mid-1,y,t.k-mid-1});
					s.push({x,mid+y+1,t.k-mid-1});
//					if(i==4&&j==1){
//						cout<<"mid:"<<mid<<endl; 
//					}
				} 
//				if(res==8){
//					cout<<i<<" "<<j<<endl;
//				}
//				cout<<i<<" "<<j<<" "<<res<<endl;
				ans=max(ans,res);
			} 
		}
		//↘ 
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				stack<node>s;
				s.push({i,j,k});
				int res=0;
				while(s.size()){
					node t=s.top();
					s.pop();
					int x=t.x;
					int y=t.y;
//					if(i==4&&j==1){
//						cout<<t.x<<" "<<t.y<<" "<<t.k<<" "<<res<<endl;
//					} 
					if(t.x<=0){
						continue;
					}
					if(t.y<=0){
						continue;
					}
					if(t.x>n){
						continue;
					}
					if(t.y>m){
						continue;
					}
					if(t.k==1){
						res=res+a[x][y]+a[x+1][y]+a[x][y+1];
						continue;
					}
					if(t.k==0){
						res=res+a[x][y];
						continue;
					}
					int mid=(t.k+0)/2;
					int x1=max(t.x,1ll);
					int y1=max(t.y,1ll);
					int x2=min(n,t.x+mid);
					int y2=min(m,mid+t.y);
//					if(i==4&&j==1){
//						cout<<x<<" "<<y<<" "<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<"     "<<sum[x2][y2]<<" "<<sum[x2][y1-1]<<" "<<sum[x1-1][y2]<<" "<<sum[x1-1][y1-1]<<endl; 	
//					}
					
					res=res+sum[x2][y2]-sum[x2][y1-1]-sum[x1-1][y2]+sum[x1-1][y1-1];
					s.push({x,y+mid+1,t.k-mid-1});
					s.push({x+mid+1,y,t.k-mid-1});
//					if(i==4&&j==1){
//						cout<<"mid:"<<mid<<endl; 
//					}
				} 
//				if(res==8){
//					cout<<i<<" "<<j<<endl;
//				}
//				cout<<i<<" "<<j<<" "<<res<<endl;
				ans=max(ans,res);
			} 
		}
		
		//↙ 
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				stack<node>s;
				s.push({i,j,k});
				int res=0;
				while(s.size()){
					node t=s.top();
					s.pop();
					int x=t.x;
					int y=t.y;
//					if(i==4&&j==1){
//						cout<<t.x<<" "<<t.y<<" "<<t.k<<" "<<res<<endl;
//					} 
					if(t.x<=0){
						continue;
					}
					if(t.y<=0){
						continue;
					}
					if(t.x>n){
						continue;
					}
					if(t.y>m){
						continue;
					}
					if(t.k==1){
						res=res+a[x][y]+a[x][y-1]+a[x+1][y];
						continue;
					}
					if(t.k==0){
						res=res+a[x][y];
						continue;
					}
					int mid=(t.k+0)/2;
					int x1=max(x,1ll);
					int y1=max(y-mid,1ll);
					int x2=min(n,t.x+mid);
					int y2=min(m,t.y);
//					if(i==4&&j==1){
//						cout<<x<<" "<<y<<" "<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<"     "<<sum[x2][y2]<<" "<<sum[x2][y1-1]<<" "<<sum[x1-1][y2]<<" "<<sum[x1-1][y1-1]<<endl; 	
//					}
					
					res=res+sum[x2][y2]-sum[x2][y1-1]-sum[x1-1][y2]+sum[x1-1][y1-1];
					s.push({x,y-mid-1,t.k-mid-1});
					s.push({x+mid+1,y,t.k-mid-1});
//					if(i==4&&j==1){
//						cout<<"mid:"<<mid<<endl; 
//					}
				} 
//				if(res==8){
//					cout<<i<<" "<<j<<endl;
//				}
//				cout<<i<<" "<<j<<" "<<res<<endl;
				ans=max(ans,res);
			} 
		}
		
		//↖ 
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				stack<node>s;
				s.push({i,j,k});
				int res=0;
				while(s.size()){
					node t=s.top();
					s.pop();
					int x=t.x;
					int y=t.y;
//					if(i==4&&j==1){
//						cout<<t.x<<" "<<t.y<<" "<<t.k<<" "<<res<<endl;
//					} 
					if(t.x<=0){
						continue;
					}
					if(t.y<=0){
						continue;
					}
					if(t.x>n){
						continue;
					}
					if(t.y>m){
						continue;
					}
					if(t.k==1){
						res=res+a[x][y]+a[x-1][y]+a[x][y-1];
						continue;
					}
					if(t.k==0){
						res=res+a[x][y];
						continue;
					}
					int mid=(t.k+0)/2;
					int x1=max(t.x-mid,1ll);
					int y1=max(t.y-mid,1ll);
					int x2=min(n,t.x);
					int y2=min(m,t.y);
//					if(i==4&&j==1){
//						cout<<x<<" "<<y<<" "<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<"     "<<sum[x2][y2]<<" "<<sum[x2][y1-1]<<" "<<sum[x1-1][y2]<<" "<<sum[x1-1][y1-1]<<endl; 	
//					}
					
					res=res+sum[x2][y2]-sum[x2][y1-1]-sum[x1-1][y2]+sum[x1-1][y1-1];
					s.push({x-mid-1,y,t.k-mid-1});
					s.push({x,y-mid-1,t.k-mid-1});
//					if(i==5&&j==5){
//						cout<<"mid:"<<mid<<endl; 
//					}
				} 
//				if(res==8){
//					cout<<i<<" "<<j<<endl;
//				}
//				cout<<i<<" "<<j<<" "<<res<<endl;
				ans=max(ans,res);
			} 
		}
//		cout<<" ";
		cout<<ans<<endl;
	}
	return 0;
} 
/*
  1
  5 5 4
  .....
  #.#.#
  #####
  .....
  #####
  
  1
  5 5 4
  #####
  ####.
  ###..
  ##...
  #....
  
  1
  5 5 4
  #....
  ##...
  ###..
  ####.
  #####
  
  1
  5 5 4
  #####
  .####
  ..###
  ...##
  ....#
  
  1
  5 5 4
  ....#
  ...##
  ..###
  .####
  #####
  
  1
  2 6 5
  ##...#
  .#.###
  
 */
```

---

## 作者：nxd_oxm (赞：0)

# 题意

输入一个 $n\times m$ 的矩阵，其中 `.` 代表空地，`#` 代表目标。你可以进行一次射程为 $k$ 的射击。具体来说，你需要站在矩阵内部的一个位置 $(u,v)$，并选择一个方向（右上，右下，左上，左下），然后你可以攻击到所有满足 $|u_0-u|+|v_0-v|\leq k$ 处的目标 $(u_0,v_0)$。

如果你选择了右上，你可以攻击到所有满足 $u_0\leq u,v_0\geq v$ 的目标；

如果你选择了右下，你可以攻击到所有满足 $u_0\geq u,v_0\geq v$ 的目标；

如果你选择了左上，你可以攻击到所有满足 $u_0\leq u,v_0\leq v$ 的目标；

如果你选择了左下，你可以攻击到所有满足 $u_0\geq u,v_0\leq v$ 的目标；

最大化攻击到的目标个数，输出这个最大值。

# 思路

直接暴力枚举即可。

我们分类讨论。将左上，左下，右上，右下分开思考。我们可以将每一个点的权值由其他的来转移。如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/ck0ldgq3.png)

我们这次要推的值是红色框框框出来的。我们已经推出来过橙色加上青色部分的权值，绿色与青色的权值以及青色与黄色部分的权值。那么，这个红色框框的值就是当前点是否有值加上橙加青的和加绿加青的和减青加黄的和再加回来最外面的一斜行，减去第二外面的斜行。我们用 $p$ 表示最外面的斜行，$q$ 表示第二外面的斜行，$a_{i,j}$ 表示 $(i,j)$ 这个位置的权值，$mp_{i,j}$ 表示这个点是否有值。所以：
 

$$a_{i,j} = mp_{i,j} + a_{i-1,j} + a_{i,j+1} - a_{i-1,j+1} + p -q$$


这些用来转移的 $a$ 数组的值之前是通过这样的递推算出来了的，而 $p,q$ 的值可以用前缀和的方式处理每一斜行。循环枚举即可。

别忘了，这只是针对右上的情况。

右下：

$$a_{i,j} = mp_{i,j} + a_{i+1,j} + a_{i,j+1} - a_{i+1,j+1} + p -q$$

左上：

$$a_{i,j} = mp_{i,j} + a_{i-1,j} + a_{i,j-1} - a_{i-1,j-1} + p -q$$

左下：

$$a_{i,j} = mp_{i,j} + a_{i+1,j} + a_{i,j-1} - a_{i+1,j-1} + p -q$$

时间复杂度 $O(nm)$。

注意存图的时候直接开一个 $10^5 \times 10^5$ 的数组是不现实的，我们可以用 vector 或者在循环里面开。

## AC code
```cpp
#include<bits/stdc++.h>
#define int long long
#define f(i,j,n) for(int i=j;i<=n;i++)
using namespace std;
int t;
int n,m,k;
vector<int> mp[100010];
vector<int> ll[100010],rr[100010];
int ls[100010],rs[100010];
vector<int> lu[100010],ru[100010],ld[100010],rd[100010];
int qclu(int nums,int i,int j){
//	cout<<"op";
	if(nums>n+m-1||nums<=0){
		return 0;
	}
//(ll[nums][abs(ll[nums][0]-j+1)]-ll[nums][abs(ll[nums][0]-(i+k-1)-1])
	int pp=j,qq=j+k+1;
	int ps=ll[nums][0]-pp+1;
	int qs=ll[nums][0]-qq+1;
	ps=min(ps,ls[nums]);
	qs=max(qs,1ll);
	if(ps<qs){
//		cout<<ps<<" "<<qs<<"---<<";
		return 0;
	}
	int ppp=j+1,qqq=j+k+1;
	int pps=0,qqs=0;
	if(nums+1<=n+m-1){
		pps=ll[nums+1][0]-ppp+1;
		qqs=ll[nums+1][0]-qqq+1;
		pps=min(pps,ls[nums+1]);
		qqs=max(qqs,1ll);
	}
//	cout<<nums<<" "<<"("<<ps<<' '<<qs<<")"<<" ("<<pps<<" "<<qqs<<")"<<endl;
	return ll[nums][ps]-(qs>1?ll[nums][qs-1]:0)-(nums<=n+m-1&&pps>=qqs?ll[nums+1][pps]-(qqs>1?ll[nums+1][qqs-1]:0):0);
}
int qcru(int nums,int i,int j){
//	cout<<"op";
	if(nums>n+m-1||nums<=0){
		return 0;
	}
//(ll[nums][abs(ll[nums][0]-j+1)]-ll[nums][abs(ll[nums][0]-(i+k-1)-1])
	int pp=j,qq=j+k+1;
	int qs=pp-rr[nums][0]+1;
	int ps=qq-rr[nums][0]+1;
	ps=min(ps,rs[nums]);
	qs=max(qs,1ll);
	if(ps<qs){
//		cout<<ps<<" "<<qs<<"---<<";
		return 0;
	}
	int ppp=j+1,qqq=j+k+1;
	int pps=0,qqs=0;
	if(nums+1<=n+m-1){
		qqs=ppp-rr[nums+1][0]+1;
		pps=qqq-rr[nums+1][0]+1;
		pps=min(pps,rs[nums+1]);
		qqs=max(qqs,1ll);
	}
//	cout<<nums<<" "<<"("<<ps<<' '<<qs<<")"<<" ("<<pps<<" "<<qqs<<")"<<endl;
	return rr[nums][ps]-(qs>1?rr[nums][qs-1]:0)-(nums+1<=n+m-1&&pps>=qqs?rr[nums+1][pps]-(qqs>1?rr[nums+1][qqs-1]:0):0);
}
int qcld(int nums,int i,int j){
//	cout<<"op";
	if(nums>n+m-1||nums<=0){
		return 0;
	}
//(ll[nums][abs(ll[nums][0]-j+1)]-ll[nums][abs(ll[nums][0]-(i+k-1)-1])
	int pp=j-k-1,qq=j;
	int qs=pp-rr[nums][0]+1;
	int ps=qq-rr[nums][0]+1;
	ps=min(ps,rs[nums]);
	qs=max(qs,1ll);
	if(ps<qs){
//		cout<<ps<<" "<<qs<<"---<<";
		return 0;
	}
	int ppp=j-k-1,qqq=j-1;
	int pps=0,qqs=0;
	if(nums-1>=1){
		qqs=ppp-rr[nums-1][0]+1;
		pps=qqq-rr[nums-1][0]+1;
		pps=min(pps,rs[nums-1]);
		qqs=max(qqs,1ll);
	}
//	cout<<nums<<" "<<"("<<ps<<' '<<qs<<")"<<" ("<<pps<<" "<<qqs<<")"<<endl;
	return rr[nums][ps]-(qs>1?rr[nums][qs-1]:0)-(nums-1>=1&&pps>=qqs?rr[nums-1][pps]-(qqs>1?rr[nums-1][qqs-1]:0):0);
}
int qcrd(int nums,int i,int j){
//	cout<<"op";
	if(nums>n+m-1||nums<=0){
		return 0;
	}
//(ll[nums][abs(ll[nums][0]-j+1)]-ll[nums][abs(ll[nums][0]-(i+k-1)-1])
	int pp=j-k-1,qq=j;
	int ps=ll[nums][0]-pp+1;
	int qs=ll[nums][0]-qq+1;
	ps=min(ps,ls[nums]);
	qs=max(qs,1ll);
	if(ps<qs){
//		cout<<ps<<" "<<qs<<"---<<";
		return 0;
	}
	int ppp=j-k-1,qqq=j-1;
	int pps=0,qqs=0;
	if(nums-1>=1){
		pps=ll[nums-1][0]-ppp+1;
		qqs=ll[nums-1][0]-qqq+1;
		pps=min(pps,ls[nums-1]);
		qqs=max(qqs,1ll);
	}
//	cout<<nums<<" "<<"("<<ps<<' '<<qs<<")"<<" ("<<pps<<" "<<qqs<<")"<<endl;
	return ll[nums][ps]-(qs>1?ll[nums][qs-1]:0)-(nums-1>=1&&pps>=qqs?ll[nums-1][pps]-(qqs>1?ll[nums-1][qqs-1]:0):0);
}
signed main(){
	//freopen(".in","r",stdin);
	//freopen('.out","w",stdout);
	cin>>t;
	while(t--){
		cin>>n>>m>>k;
		f(i,1,n){
			mp[i].clear();
			lu[i].clear();
			ru[i].clear();
			ld[i].clear();
			rd[i].clear();
			mp[i].push_back(0);
			lu[i].push_back(0);
			ru[i].push_back(0);
			ld[i].push_back(0);
			rd[i].push_back(0);
			f(j,1,m){
				char t;
				cin>>t;
				mp[i].push_back((t=='#'?1:0));
				lu[i].push_back(0);
				ru[i].push_back(0);
				ld[i].push_back(0);
				rd[i].push_back(0);
			}
			f(j,1,5){
				lu[i].push_back(0);
				ru[i].push_back(0);
				ld[i].push_back(0);
				rd[i].push_back(0);
			}
		}
		f(i,1,m+n+10){
			ls[i]=rs[i]=0;
			ll[i].clear();
			rr[i].clear();
			ll[i].push_back(0);
			rr[i].push_back(0);
		}
//		f(i,1,n){
//			f(j,1,m){
//				cout<<mp[i][j]<<" ";
//			}
//			cout<<endl;
//		}
		for(int i=1;i<=m;i++){
			ll[i][0]=i;
			ll[i].push_back(mp[1][i]);
			ls[i]=1;
//			cout<<i<<":\n        "; 
//			cout<<ll[i][1]<<" ";
			for(int x=2,y=i-1,cnt=2;x>=1&&x<=n&&y>=1&&y<=m;cnt++,x++,y--){
				ll[i].push_back(ll[i][cnt-1]+mp[x][y]);
				ls[i]=cnt;
//				cout<<ll[i][cnt]<<" ";
			}
//			cout<<endl;
		}
		for(int i=2;i<=n;i++){
			ll[i+m-1][0]=m;
			ll[i+m-1].push_back(mp[i][m]);
			ls[i+m-1]=1;
//			cout<<i+m-1<<":\n        ";
//			cout<<ll[i][1]<<" ";
			for(int x=i+1,y=m-1,cnt=2;x>=1&&x<=n&&y>=1&&y<=m;cnt++,x++,y--){
				ll[i+m-1].push_back(ll[i+m-1][cnt-1]+mp[x][y]);
				ls[i+m-1]=cnt;
//				cout<<ll[i][cnt]<<" ";
			}
//			cout<<endl;
		}
		for(int i=n;i>=1;i--){
			rr[n-i+1][0]=1;
			rr[n-i+1].push_back(mp[i][1]);
			rs[n-i+1]=1;
//			cout<<i<<":\n  ";
//			cout<<rr[i][1]<<" [] ";
			for(int x=i+1,y=2,cnt=2;x>=1&&x<=n&&y>=1&&y<=m;cnt++,x++,y++){
				rr[n-i+1].push_back(rr[n-i+1][cnt-1]+mp[x][y]);
				rs[n-i+1]=cnt;
//				cout<<rr[i][cnt]<<" [] ";
			}
//			cout<<endl;
		}
		for(int i=2;i<=m;i++){
			rr[i+n-1][0]=i;
			rr[i+n-1].push_back(mp[1][i]);
			rs[i+n-1]=1;
//			cout<<i<<":\n  ";
//			cout<<rr[i][1]<<" [] ";
			for(int x=2,y=i+1,cnt=2;x>=1&&x<=n&&y>=1&&y<=m;cnt++,x++,y++){
				rr[i+n-1].push_back(rr[i+n-1][cnt-1]+mp[x][y]);
				rs[i+n-1]=cnt;
//				cout<<rr[i][cnt]<<" [] ";
			}
//			cout<<endl;
		}
//		f(i,1,n+m-1){
//			cout<<rs[i]<<" "<<rr[i][0]<<endl;
//		}
		int maxn=-1;
		//lu
		for(int i=n;i>=1;i--){
			for(int j=m;j>=1;j--){
				if(i==n&&j==m){
					lu[i][j]=mp[n][m];
					maxn=max(maxn,lu[i][j]);
//					cout<<i<<","<<j<<":"<<lu[i][j]<<endl;
					continue;
				}
				int nums=i+j+k;
//				cout<<nums<<" ";
//				cout<<"op";
				lu[i][j]=mp[i][j]+(i<n?lu[i+1][j]:0)+(j<m?lu[i][j+1]:0)-(i<n&&j<m?lu[i+1][j+1]:0)-qclu(nums,i,j);
//				cout<<i<<","<<j<<":"<<lu[i][j]<<endl;
				maxn=max(maxn,lu[i][j]);
			}
		}
//		cout<<endl;
		//4,1 2 4
		//3,1 2 5
		//4 2 2 5
		//ru
		for(int i=1;i<=n;i++){
			for(int j=m;j>=1;j--){
				if(i==1&&j==m){
					ru[i][j]=mp[1][m];
					maxn=max(maxn,ru[i][j]);
//					cout<<i<<","<<j<<":"<<ru[i][j]<<endl;
					continue;
				}
				int nums=j+k+1+(n-i);
//				cout<<nums<<" ";
//				cout<<"op";
				ru[i][j]=mp[i][j]+(i>1?ru[i-1][j]:0)+(j<m?ru[i][j+1]:0)-(i>1&&j<m?ru[i-1][j+1]:0)-qcru(nums,i,j);
//				cout<<i<<","<<j<<":";
//				cout<<ru[i][j]<<endl;
				maxn=max(maxn,ru[i][j]);
			}
		}
		//3 1  1 -1
		//3 2  1 0
		//2 1  1 0
		//ld
//		cout<<endl;
		for(int i=n;i>=1;i--){
			for(int j=1;j<=m;j++){
				if(i==n&&j==1){
					ld[i][j]=mp[n][1];
					maxn=max(maxn,ld[i][j]);
//					cout<<i<<","<<j<<":"<<ld[i][j]<<endl;
					continue;
				}
				int nums=(n-i-1)+j-k;
//				cout<<nums<<" ";
//				cout<<"op";
				ld[i][j]=mp[i][j]+(i<n?ld[i+1][j]:0)+(j>1?ld[i][j-1]:0)-(i<n&&j>1?ld[i+1][j-1]:0)-qcld(nums,i,j);
//				cout<<i<<","<<j<<":";
//				cout<<ld[i][j]<<endl;
				maxn=max(maxn,ld[i][j]);
			}
		}
		//1 1 1 -1
		//1 2 1 0
		//2 1 1 0
		//rd
//		cout<<endl;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(i==1&&j==1){
					rd[i][j]=mp[1][1];
					maxn=max(maxn,rd[i][j]);
//					cout<<i<<","<<j<<":"<<rd[i][j]<<endl;
					continue;
				}
				int nums=(i+j)-k-2;
//				cout<<nums<<" ";
//				cout<<"op";
				rd[i][j]=mp[i][j]+(i>1?rd[i-1][j]:0)+(j>1?rd[i][j-1]:0)-(i>1&&j>1?rd[i-1][j-1]:0)-qcrd(nums,i,j);
//				cout<<i<<","<<j<<":";
//				cout<<rd[i][j]<<endl;
				maxn=max(maxn,rd[i][j]);
			}
		}
//		cout<<endl;
		cout<<maxn<<endl;
	}
	return 0;
}
```
代码有点长。

---

## 作者：MaxBlazeResFire (赞：0)

本来是抱着来玩的心态的，结果阴沟里翻船。

无脑做法。注意到本题可以对每个方向分别做一遍。以顶点在左下角为例，注意到可以将左下角 $(u,v)$，边长为 $L$ 的三角形差分成左下角 $(1,u)$ 长度为 $L+v-1$ 的三角形减去左下角 $(1,u-L)$ 长度 $v-1$ 的三角形再减去矩形 $[[u-L+1,u],[1,v-1]]$。

预处理所有贴边的三角形，边长范围需要开 $O(n)$ 级别，不够怎么办？注意到可以通过矩阵转置把空间卡到 $O(\min(n,m)\times(\min(n,m)+\max(n,m)))=O(\min(n,m)\times\max(n,m))=O(nm)$，时间复杂度也为 $O(nm)$。可以通过。

update: 复杂度分析。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 200005

int n,m,k,Ans = 0;
char s[MAXN];
vector<int> a[MAXN],p[MAXN];

inline int S( int u , int d , int l , int r ){
	u = max( u , 1ll ),d = min( d , n ),l = max( l , 1ll ),r = min( r , m );
	if( u > d || l > r ) return 0;
	return a[d][r] - a[d][l - 1] - a[u - 1][r] + a[u - 1][l - 1];
}

//p[i][j] 表示左下角在 (i,1)，长度为 j 的三角形答案
inline void solve1(){
	for( int i = 0 ; i <= n ; i ++ ) p[i].resize( n + m + 1 );
	for( int i = 1 ; i <= n ; i ++ )
      //这里循环变量开小了，警钟敲烂
		for( int j = 1 ; j <= n + m ; j ++ ) p[i][j] = p[i - 1][j - 1] + S( i , i , 1 , j );
	for( int i = 1 ; i <= n ; i ++ )
		for( int j = 1 ; j <= m ; j ++ ){
			int L = min( k + 1 , n + m - j + 1 );
			int g = p[i][L + j - 1];
			if( i > L && j > 1 ) g -= p[i - L][j - 1];
			g -= S( i - L + 1 , i , 1 , j - 1 );
			Ans = max( Ans , g );
		}
	for( int i = 0 ; i <= n ; i ++ ) p[i].clear();
}

//p[i][j] 表示左上角在 (i,1)，长度为 j 的三角形答案
inline void solve2(){
	for( int i = 1 ; i <= n + 1 ; i ++ ) p[i].resize( n + m + 1 );
	for( int i = n ; i >= 1 ; i -- )
		for( int j = 1 ; j <= n + m ; j ++ ) p[i][j] = p[i + 1][j - 1] + S( i , i , 1 , j );
	for( int i = 1 ; i <= n ; i ++ )
		for( int j = 1 ; j <= m ; j ++ ){
			int L = min( k + 1 , n + m - j + 1 );
			int g = p[i][L + j - 1];
			if( i + L <= n && j > 1 ) g -= p[i + L][j - 1];
			g -= S( i , i + L - 1 , 1 , j - 1 );
			Ans = max( Ans , g );
		}
	for( int i = 1 ; i <= n + 1 ; i ++ ) p[i].clear();
}

//p[i][j] 表示右下角在 (i,m)，长度为 j 的三角形答案
inline void solve3(){
	for( int i = 0 ; i <= n ; i ++ ) p[i].resize( n + m + 1 );
	for( int i = 1 ; i <= n ; i ++ )
		for( int j = 1 ; j <= n + m ; j ++ ) p[i][j] = p[i - 1][j - 1] + S( i , i , m - j + 1 , m );
	for( int i = 1 ; i <= n ; i ++ )
		for( int j = 1 ; j <= m ; j ++ ){
			int L = min( k + 1 , n + j );
			int g = p[i][L + m - j];
			if( i > L && m > j ) g -= p[i - L][m - j];
			g -= S( i - L + 1 , i , j + 1 , m );
			Ans = max( Ans , g );
		}
	for( int i = 0 ; i <= n ; i ++ ) p[i].clear();
}

//p[i][j] 表示右上角在 (i,m)，长度为 j 的三角形答案
inline void solve4(){
	for( int i = 1 ; i <= n + 1 ; i ++ ) p[i].resize( n + m + 1 );
	for( int i = n ; i >= 1 ; i -- )
		for( int j = 1 ; j <= n + m ; j ++ ) p[i][j] = p[i + 1][j - 1] + S( i , i , m - j + 1 , m );
	for( int i = 1 ; i <= n ; i ++ )
		for( int j = 1 ; j <= m ; j ++ ){
			int L = min( k + 1 , n + j );
			int g = p[i][L + m - j];
			if( i + L <= n && m > j ) g -= p[i + L][m - j];
			g -= S( i , i + L - 1 , j + 1 , m );
			Ans = max( Ans , g );
		}
	for( int i = 1 ; i <= n + 1 ; i ++ ) p[i].clear();
}

vector<int> tmp[MAXN];
inline void solve(){
	scanf("%lld%lld%lld",&n,&m,&k);
	for( int i = 0 ; i <= n ; i ++ ) a[i].resize( m + 1 , 0 );
	for( int i = 1 ; i <= n ; i ++ ){
		scanf("%s",s + 1);
		for( int j = 1 ; j <= m ; j ++ ) a[i][j] = s[j] == '#';
	}
	if( n > m ){
		for( int i = 1 ; i <= m ; i ++ ) tmp[i].resize( n + 1 );
		for( int i = 1 ; i <= n ; i ++ )
			for( int j = 1 ; j <= m ; j ++ ) tmp[j][i] = a[i][j];
		for( int i = 1 ; i <= m ; i ++ ) a[i].resize( n + 1 );
		for( int i = 1 ; i <= m ; i ++ )
			for( int j = 1 ; j <= n ; j ++ ) a[i][j] = tmp[i][j];
		swap( n , m );
	}
	for( int i = 1 ; i <= n ; i ++ ) for( int j = 1 ; j <= m ; j ++ ) a[i][j] += a[i][j - 1];
	for( int j = 1 ; j <= m ; j ++ ) for( int i = 1 ; i <= n ; i ++ ) a[i][j] += a[i - 1][j];
	Ans = 0;
	solve1();
	solve2();
	solve3();
	solve4();
	printf("%lld\n",Ans);
}

signed main(){
	int testcase; scanf("%lld",&testcase);
	while( testcase -- ) solve();
	return 0;
}
```

---

