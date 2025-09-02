# ANARC07C - Rotating Rings

## 题目描述

任何方形网格都可以看作一个或多个环，一个套在一个里面。例如，如图 (a) 所示，一个 5 x 5 的网格由三个环组成，编号为 1、2 和 3（从外到内）。一个大小为 $N$ 的方形网格被称为有序的，如果它包含从 1 到 $N^2$ 的值，并且按行优先顺序排列，如图 (b) 所示，其中 $N = 4$。我们希望确定给定的方形网格是否可以通过仅旋转其环来排序。例如，图 (c) 中的网格可以通过将第一个环逆时针旋转两个位置，并将第二个环顺时针旋转一个位置来排序。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP4568/de2efad7acfbae02d1e24e4c5bae5c3fbd72210c.png)

# 题解

## 作者：hinin (赞：0)

### 题意

判断一个给定的方形网格是否可以通过旋转其环来排序。排序的标准是网格中的数值按行优先顺序排列，且数值从 $1$ 到 $N^2$ 不重复。

### 思路

一个简单的模拟。先预处理有序矩阵，自外向内提取环：环的数量为 $\frac{N + 1}{2}$。

对于每个环，我们将其旋转到最小值的位置，然后与目标环进行比较。最后检查唯一性。

### 代码

``` cpp
#include <bits/stdc++.h>
// #pragma GCC optimize("Ofast", "-funroll-all-loops")
#define ll long long
#define pii pair<int, int>

#define y1 gigay
#define x first
#define y second

using namespace std;

const int N = 1e3 + 1, M = 1e6 + 1; 
bool vls[M];
int n, tms, g[N][N];
vector<int> obj[N];
vector<int> now[N]; 

int toInt(int i, int j)
{ return i * n + j + 1; }

int main()
{
	ios::sync_with_stdio(false); 
	cin.tie(nullptr); 
	
	while (cin >> n) {
		if(not n) { break; }
		
		int num = (n + 1) / 2;

		for (int k = 0; k < num; k ++) {
			obj[k].clear(); 
			
			for (int j = k; j < n - k; j ++) 
			{ obj[k].push_back(toInt(k, j)); }

			for (int i = k + 1; i <= n - k - 2; i ++) 
			{ obj[k].push_back(toInt(i, n - k - 1));}

			for (int j = n - k - 1; j >= k; j --) 
			{ obj[k].push_back(toInt(n - k - 1, j)); }

			for (int i = n - k - 2; i > k; i --) 
			{ obj[k].push_back(toInt(i, k)); }
		}

		if (n & 1) { obj[num - 1].erase(obj[num - 1].begin()); }

		for (int i = 0; i <= n * n; i ++) { vls[i] = false; }

		bool flg = false;

		for (int i = 0; i < n; i ++) {
			for (int j = 0; j < n; j ++) {
				cin >> g[i][j]; 

				if (vls[g[i][j]]) { flg = true; }

				vls[g[i][j]] = true;
			}
		}

		for (int k = 0; k < num; k ++) {
			now[k].clear(); 
			
			for (int j = k; j < n - k; j ++) 
			{ now[k].push_back(g[k][j]); }

			for (int i = k + 1; i <= n - k - 2; i ++) 
			{ now[k].push_back(g[i][n - k - 1]); }

			for (int j = n - k - 1; j >= k; j --) 
			{ now[k].push_back(g[n - k - 1][j]); }

			for (int i = n - k - 2; i > k; i --) 
			{ now[k].push_back(g[i][k]); }
		}

		if (n & 1) { now[num - 1].erase(now[num - 1].begin()); }

		if (!flg) {
			for (int k = 0; k < num; k ++) {
				rotate(now[k].begin(), min_element(now[k].begin(), now[k].end()), now[k].end());

				if (now[k] != obj[k]) {
					flg = true;
					break;
				}
			}
		}

		cout << ++ tms << ". "; 
		
		if(flg) { cout << "NO" << endl; }
		else { cout << "YES" << endl; }
	}

	return 0;
}
```

---

## 作者：_maple_leaf_ (赞：0)

## 题意
当一个 $N\times N$ 矩阵中的元素刚好包含 $1\sim N\times N$ 这 $N \times N$ 个值，且按行从左到右，换行从左开始的顺序填入一个数组，这个数组是按 $1\sim N\times N$ 排列的时，这个矩阵被称为有序的。同时一个 $N\times N$ 的矩阵被分为 $\lceil \frac{N}{2}\rceil$ 个环，如下图，同色、同数字的就是一个环：

![](https://cdn.luogu.com.cn/upload/image_hosting/nuygy373.png)

转动环就是按照行从左到右，换行从左开始的顺序填入一个数组，将这个数组的开头丢到结尾去，然后再按顺序填回去。

## 注意
题面中的 $1\le N \le 100$ 是错误的，实测 $N > 100$。[link](https://www.luogu.com.cn/record/197584522)

## 思路
一个很简单但有一点细节的模拟。

先预处理出一个有序的矩阵，然后拆出环里的元素，丢到 $\lceil \frac{N}{2}\rceil$ 个 vector 里，然后再在输入的矩阵拆出这么几个环，然后在第 $i$ 个环上旋转 $[n-(i-1)\times 2-1]\times 4$ 次，边转边与有序的环比较，如果有相等就到下一个环，一直没有就可以退出循环输出 `NO`，否则所有环都有相等就输出 `YES`。

## 代码
```cpp
//by _maple_leaf_ uid:964876
const int N=1145;
int cnt;
int n,m;
bool f;
int mp[N][N];
int a[N][N];
queue<int>s[N>>1];
bool fff[N*N];
signed main(){
    while(1){
        memset(fff,0,sizeof fff);
        cnt++;
        n=read();
        if(!n)return 0;
        f=1;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                a[i][j]=read();
            }
        }
        for(int i=1;i<=n*n;i++)mp[(int)ceil((double)i/n)][(i-1)%n+1]=i;//填出有序矩阵
        m=(n+1)>>1;
        for(int i=1;i<=m;i++){
            while(!s[i].empty())s[i].pop();
            int h1=i,h2=n-i+1,l1=i,l2=n-i+1;
            for(int j=l1;j<=l2;j++)s[i].push(mp[h1][j]);
            for(int j=h1+1;j<=h2-1;j++)s[i].push(mp[j][l2]);
            if(h2!=h1)for(int j=l2;j>=l1;j--)s[i].push(mp[h2][j]);
            if(l2!=l1)for(int j=h2-1;j>=h1+1;j--)s[i].push(mp[j][l1]);//拆出有序矩阵的第i个环
        }
        for(int i=1;i<=m;i++){
            int h1=i,h2=n-i+1,l1=i,l2=n-i+1,temp=0;
            queue<int>v;
            while(!v.empty())v.pop();
            for(int j=l1;j<=l2;j++){
                v.push(a[h1][j]);
                temp++;
            }
            for(int j=h1+1;j<=h2-1;j++){
                v.push(a[j][l2]);
                temp++;
            }
            if(h1!=h2){
                for(int j=l2;j>=l1;j--){
                    v.push(a[h2][j]);
                    temp++;
                }
            }
            if(l2!=l1){
                for(int j=h2-1;j>=h1+1;j--){
                    v.push(a[j][l1]);
                    temp++;
                }
            }//拆下第i个环
            bool t=0;
            while(temp--){
                if(v==s[i]){//判断
                    t=1;
                    break;
                }
                v.push(v.front());//转
                v.pop();
            }if(!t){//无解，退出循环
                f=0;
                break;
            }
        }write(cnt);
        putchar('.');
        putchar(' ');
        if(f)puts("YES");
        else puts("NO");
    }
#if DEBUG
    debug();
#endif
    return 0;
}//~*完结撒花*~
#if DEBUG
bool Memory_end;
void debug(){
    cerr<<"Time: "<<clock()<<" ms\n";
    cerr<<fixed<<setprecision(6)<<"Memory: "<<abs(&Memory_start-&Memory_end)/1024.0/1024.0<<" MB";
}
#endif
```

---

