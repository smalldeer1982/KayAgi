# Shifting Sort

## 题目描述

The new generation external memory contains an array of integers $ a[1 \ldots n] = [a_1, a_2, \ldots, a_n] $ .

This type of memory does not support changing the value of an arbitrary element. Instead, it allows you to cut out any segment of the given array, cyclically shift (rotate) it by any offset and insert it back into the same place.

Technically, each cyclic shift consists of two consecutive actions:

1. You may select arbitrary indices $ l $ and $ r $ ( $ 1 \le l < r \le n $ ) as the boundaries of the segment.
2. Then you replace the segment $ a[l \ldots r] $ with it's cyclic shift to the left by an arbitrary offset $ d $ . The concept of a cyclic shift can be also explained by following relations: the sequence $ [1, 4, 1, 3] $ is a cyclic shift of the sequence $ [3, 1, 4, 1] $ to the left by the offset $ 1 $ and the sequence $ [4, 1, 3, 1] $ is a cyclic shift of the sequence $ [3, 1, 4, 1] $ to the left by the offset $ 2 $ .

For example, if $ a = [1, \color{blue}{3, 2, 8}, 5] $ , then choosing $ l = 2 $ , $ r = 4 $ and $ d = 2 $ yields a segment $ a[2 \ldots 4] = [3, 2, 8] $ . This segment is then shifted by the offset $ d = 2 $ to the left, and you get a segment $ [8, 3, 2] $ which then takes the place of of the original elements of the segment. In the end you get $ a = [1, \color{blue}{8, 3, 2}, 5] $ .

Sort the given array $ a $ using no more than $ n $ cyclic shifts of any of its segments. Note that you don't need to minimize the number of cyclic shifts. Any method that requires $ n $ or less cyclic shifts will be accepted.

## 说明/提示

Explanation of the fourth data set in the example:

1. The segment $ a[2 \ldots 4] $ is selected and is shifted to the left by $ 2 $ : $ [2, {\color{blue}{5, 1, 4}}, 3] \longrightarrow [2, {\color{blue}{4, 5, 1}}, 3] $
2. The segment $ a[1 \ldots 5] $ is then selected and is shifted to the left by $ 3 $ : $ [{\color{blue}{2, 4, 5, 1, 3}}] \longrightarrow [{\color{blue}{1, 3, 2, 4, 5}}] $
3. After that the segment $ a[1 \ldots 2] $ is selected and is shifted to the left by $ 1 $ : $ [{\color{blue}{1, 3}}, 2, 4, 5] \longrightarrow [{\color{blue}{3, 1}}, 2, 4, 5] $
4. And in the end the segment $ a[1 \ldots 3] $ is selected and is shifted to the left by $ 1 $ : $ [{\color{blue}{3, 1, 2}}, 4, 5] \longrightarrow [{\color{blue}{1, 2, 3}}, 4, 5] $

## 样例 #1

### 输入

```
4
2
2 1
3
1 2 1
4
2 4 1 3
5
2 5 1 4 3```

### 输出

```
1
1 2 1
1
1 3 2
3
2 4 1
2 3 1
1 3 2
4
2 4 2
1 5 3
1 2 1
1 3 1```

# 题解

## 作者：EternalHeart1314 (赞：7)

### [题目传送门](https://www.luogu.com.cn/problem/CF1579B)

# 思路

可以发现此题的 $n$ 非常小，小到离谱，只有 $50$，那么我们的枚举算法便新鲜出炉了。

先枚举每个位置，也就是 $1\sim n$，再往后找，找到当前位置应该有的数字，再把它通过左移移到当前位置，注意细节很多，不要被绕迷糊了。

时间复杂度 $O(tn^2)$。

# Code
```
#include<bits/stdc++.h>
using namespace std;

const int N(55);
int t, n, a[N], b[N], c[N], d[N], ans, k, x;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> t;
	while(t --) {
		cin >> n;
		ans = 0;
		for(int i(1); i <= n; ++ i) {
			cin >> a[i];
			c[i] = a[i];
		}
		sort(c + 1, c + n + 1);
		for(int i(1); i <= n; ++ i) {
			for(int j(i); j <= n; ++ j) {
				if(a[j] == c[i]) {
					k = j;
					break;
				}
			}
			d[i] = k;
			if(k > i) {
				++ ans;
			}
			for(int j(i); j <= k; ++ j) {
				x = j + k - i;
				if(x > k) {
					x = x - k + i - 1;
				}
				b[j] = a[x];
			}
			for(int j(i); j <= k; ++ j) {
				a[j] = b[j];
			}
		}
		cout << ans << '\n';
		for(int i(1); i <= n; ++ i) {
			if(d[i] > i) {
				cout << i << ' ' << d[i] << ' ' << d[i] - i << '\n';
			}
		}
	}
	return 0;
}
```

### 珍惜生命，远离抄袭

---

## 作者：zhangqin123 (赞：4)

### 题意
对于一个数组，对其进行操作，让区间 $[l,r]$ 的数左移 $d$ 位,使得最后的数变得有序，输出操作次数、$l$、$r$、$d$，答案不唯一。
### 思路


1. 由于a的数组范围为$-10 ^ 9 \leq a_i \leq 10^9$，对其进行离散化 , 由 $ n \leq 50$，所以离散化后最大的值不超过 $50$。

1. 记录当前未排序部分最小值的下标，贪心地将未排序部分的最小值移至未排序部分的最前面，由于每次左移变换导致位置不确定，所以每次排序后应更新未排序部分最小值的下标。

1. 仔细研究可以发现：左移变换后的位置顺序是有规律的，即为  $a_l=min$ , $a_x= a_{x-1}$ （ $l+1\leq x \leq r$, $min$  为当前未排序部分的最小值）
### 代码部分
```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
using namespace std;
int t,a[51],b[51],sum[51],k[51][51],ans1[51],ans2[51],ans3[51],ans;
int main()
{
      scanf("%d",&t);
      while(t--)
      {
          memset(a,0,sizeof(a));
          memset(b,0,sizeof(b));
          memset(sum,0,sizeof(sum));
          memset(k,0,sizeof(k));
          int n,m,sumx=0,h=1;
          ans=0;
          scanf("%d",&n);
          for(int i=1;i<=n;i++)
          {
              scanf("%d",&a[i]);
              b[i]=a[i];
          }
          // 离散化操作 
          sort(b+1,b+1+n);
          m=unique(b+1,b+1+n)-b-1;
          for(int i=1;i<=n;i++)
              a[i]=lower_bound(b+1,b+1+m,a[i])-b;
          // 记录 当前最小值的位置 
          for(int i=1;i<=n;i++)
              if(a[i]==h) sum[1]++,k[1][sum[1]]=i;
          for(int q=1;q<=50;q++)  
          {
              if(!sum[q]) continue;
              for(int i=1;i<=sum[q];i++)
              {
                  sumx++;
                  if(sumx!=k[q][i]) 
                  {
                      ans++; // 记录答案，将最小值的位置移至未排序部分的最前面 
                      ans1[ans]=sumx,ans2[ans]=k[q][i],ans3[ans]=k[q][i]-sumx;
                      //printf("%d %d %d\n",sumx,k[q][i],k[q][i]-sumx);
                      for(int x=sumx;x<=k[q][i];x++)
                          b[x]=a[x];
                      for(int x=sumx+1;x<=k[q][i];x++)
                          a[x]=b[x-1];
                      a[sumx]=q;
                  }
              }
              h++;
              for(int i=sumx+1;i<=n;i++) // 重新记录 
              {
                  if(a[i]==h) sum[h]++,k[h][sum[h]]=i;
              }
          }
          printf("%d\n",ans);
          for(int i=1;i<=ans;i++)
          {
              printf("%d %d %d\n",ans1[i],ans2[i],ans3[i]);
          }
      }
      return 0;
}
```



---

## 作者：Cold_Eyes_bystander (赞：4)

这道题因为 $ n \le 50,t \le 1000$，所以 $O(t \times n^{2})$ 不会超时。

这道题我看许多 dalao 用的方法蒟蒻都看不懂，自己想了一下，用插入排序的思想写了出来。

我们可以把 $d$ 锁定成 $1$，这样就可以实现把某个元素移到前面，并且 操作次数 $\le n$，按这种思路，我们就可以实现排序啦。

代码献上。

```c++
#include <bits/stdc++.h>
using namespace std;
int a[1919810],b[1919810],c[1919810],d[1919810];
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        int cnt=0;
        for(int i=1;i<=n;i++) cin>>a[i];
        for(int i=n;i>=1;i--)
        {
            int x=a[i],j=i+1;
            while(j<=n&&a[j]<x)
            {
                a[j-1]=a[j];
                j++;
            }
            j--;
            a[j]=x;
            if(j!=i)
            {
                cnt++;
                b[cnt]=i,c[cnt]=j,d[cnt]=1;
            }
        }
        cout<<cnt<<endl;
        for(int i=1;i<=cnt;i++)
        {
            cout<<b[i]<<" "<<c[i]<<" "<<d[i]<<endl;
        }
    }
    return 0;
}
```

---

## 作者：Z_AuTwT (赞：2)

# CF1579B
## 题目大意：

对于一个序列，每次可以选择一个区间 $[l,r]$ 将其中的数循环左移 $d$ 位，要将这个序列排序，求最小的操作次数。

## 思路：
分析题意，可以发现我们每次操作至少可以让这个序列中的一个数字归位。而对于其他数字，则无法确定。

其实，这就类似于一个冒泡排序的思想，每次找出最小值，将这个最小值归位。

这里有一个细节需要注意，就是有可能在之前的操作之后，当前的最小值已经到了该到的位置，就不用变了。

在这里，还需要用一个数组来存一下中间的改变方式。

## 代码：
```c++
#include<bits/stdc++.h>
using namespace std;
int arr[100],cun[100][3];
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++) cin>>arr[i];
		memset(cun,0,sizeof(cun));//多测清空
		int v=1,cnt=0,xb=0;
		for(int i=1;i<=n;i++){
			int minn=2e9,id=0;
			for(int j=v;j<=n;j++){//寻找最小值
				if(arr[j]<minn){
					minn=arr[j];
					id=j;
				}
			}
			for(int j=id;j>v;j--) swap(arr[j],arr[j-1]);//冒泡
			if(v!=id){//特判
				cun[++xb][0]=v;
				cun[xb][1]=id;
				cun[xb][2]=id-v;
				cnt++;
			}
			v++;
		}
		cout<<cnt<<"\n";
		for(int i=1;i<=xb;i++) cout<<cun[i][0]<<" "<<cun[i][1]<<" "<<cun[i][2]<<"\n";
	}
} 
```

---

## 作者：Isshiki·Iroha (赞：2)

## 题解

[题目传送门](https://www.luogu.com.cn/problem/CF1579B)

[点我获得更好的阅读体验](https://www.luogu.com.cn/blog/yousa22/solution-cf1579b)

### 题意

在 $n$ 次操作内对数组排序，每一次排序把一段区间左移，有两个重要性质。

- 对于任意一个数，可以一次操作到任意一个位置

设当前在 $x_i$，要到 $x_j$（假设 $x_i$ 在右边）

只需要把 $(x_i,x_j)$ 移动 $x_j-x_i$ 即可。

- 有足够的次数把每一个数都操作一次

有这两点可以想到每一次把最小的数复原，但是有重复。

例如：$2,1,1$

由于有足够的次数把每一个数都操作一次，我们可以把数组看成：

例如：$2,1,3$

即离散化的时候，做一点改动，离散为 $1$ 到 $n$ 的数列。可能不太清楚，看代码应该懂了；

[Code](https://codeforces.com/contest/1579/submission/146346040)


---

## 作者：IngSoc1984 (赞：2)

## 题意
在数组中选定一个起始为 $l$ 终点为 $r$ 的段，向左循环 $d$ 次。  
要求循环不超过数组长度 $n$ 。  
输出操作次数及过程。
## 循环移位的实现
$[ 5,4,3,2,1 ]->[ 1,5,4,3,2 ]$  
  
思路是前后交换，可达到移位的效果。
```cpp
void sft(int s,int e,int d){
	for(int i=0;i<d;i++){//d表示重复循环移位次数
		for(int j=s;j<e;j++){	
			swap(m[j],m[j+1]);//反复交换即可
            
		}
	}
	
}
```
## 代码思路
每次找出最小者，通过循环移位放到位置 $ i $（将前 $ i $ 个数字固定）。  
将每次操作存储下来即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define INF 2e9
int m[55];
void sft(int s,int e,int d){//移位
	for(int i=0;i<d;i++){
		for(int j=s;j<e;j++){
			swap(m[j],m[j+1]);
		}
	}
	
}
struct node{//单次操作记录
	int l,r,dd;
};
queue<node>q;//所有操作记录

int main(){
	int t;
	cin>>t;
	while(t--){
		int opr=0;//操作次数
		memset(m,0,sizeof(m));
		int n;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>m[i];
		}
		for(int i=1;i<n;i++){
			int minm=INF,minid=-1;
			for(int j=i;j<=n;j++){//找出最小者
				if(m[j]<minm){
					minm=m[j];
					minid=j;
				}
			}
			sft(i,minid,minid-i);//移动到i处
			opr++;//操作次数加一
			q.push(node{i,minid,minid-i});//存储
		}
		cout<<opr<<endl;
		for(int i=0;i<opr;i++){//输出记录
			node now=q.front();
			q.pop();
			cout<<now.l<<' '<<now.r<<' '<<now.dd<<endl;
		}
	}
	
	return 0;
}
```


---

## 作者：yangzd (赞：2)

# 题目大意

给出一个数组，$n$ 个元素，只能进行 $1$ 种操作，选定 $l,r,d$ ，表示将 $l$ 到 $r$ 的区间，左移 $d$ 位，最左边左移到最右边，总次数不超过 $n$，每次操作 $d>0$

# 分析

数据范围小，直接暴力移动，每回将最小的数移动到左边，第 $i$ 轮维护好前 $i$ 个数，因为移动位数不能为 $0$，所以将答案存下来，之后输出

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

long long n,m,t,k;
long long s[100005],dp[100005],f[10005];
char g[100005];

string str;

vector<long long> vec;

signed main()
{
	ios::sync_with_stdio(0);
	
    cin >> t;
    
    while(t--) 
    {
    	cin >> n;
	
		vec.clear();
	
		for (long long i=1; i<=n; i++)
			cin >> s[i];
		
		for (long long i=1; i<n; i++)
		{
			long long k=i;
		
			for (long long j=i; j<=n; j++)
				if (s[j]<s[k])
					k=j;
				
			if (k==i)
				continue;
			
			vec.push_back(i);
			vec.push_back(n);
			vec.push_back(k-i);
		
			for (long long j=i; j<=n; j++)
				f[j]=s[(j+k-i-i)%(n-i+1)+i];
			
			for (long long j=i; j<=n; j++)
				s[j]=f[j];
		}

		cout << vec.size()/3 << endl;
	
		for (long long i=0; i<vec.size(); i++)
		{
			if (i && i%3==0)
				cout << endl;
			
			else if (i)
				cout << " " << endl;
			
			cout << vec[i];
		
		}
    }
    
    return 0;
}
```

---

## 作者：huyangmu (赞：2)

这道题因为数据范围小，直接暴力就可以过。

先将原数组排序，然后双重循环枚举数组中每个元素排序后的位置。如果一个元素的位置在它排序前位置的后面，就肯定是左移过来的，直接模拟左移即可，并用另一个数组记录这个位置，给答案加一。

最后枚举记录位置的数组，每次输出即可。

### AC Code

```cpp

#include<bits/stdc++.h>
using namespace std;
const int NR = 55;
int T,n,a[NR],b[NR],c[NR],dis[NR],ans;
int main (){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin >> T;
	while (T--){
		cin >> n;
		for (int i = 1;i <= n; ++i) {
			cin >> a[i];
			b[i] = a[i];
		}
		sort(b + 1,b + n + 1);	
		ans = 0;	
		int tmp,tmp2;
		for (int i = 1;i <= n; ++i){
			for (int j = i;j <= n; ++j){
				if (b[i] == a[j]){
					tmp = j;					
					break;
				}			
			}
			dis[i] = tmp;
			if (tmp > i) ++ans;
			for (int j = i;j <= tmp; ++j){
				tmp2 = j + tmp - i;
				if (tmp2 > tmp) tmp2 = tmp2 - tmp + i - 1;
				c[j] = a[tmp2];
			}
			for (int j = i;j <= tmp; ++j){
				a[j] = c[j];
			}
		}
		cout << ans << '\n';
		for (int i = 1;i <= n; ++i){
			if (dis[i] <= i) continue;
			cout << i << ' ' << dis[i] << ' ' << dis[i] - i << '\n';
		}
	}
	return 0;
}


---

## 作者：L_xcy (赞：0)

### 解题思路

1. 不用离散化。
2. 暴力。

循环 $1$ 到 $n$，每次的目的是让这个位置应存的数归位。

从当前位置往后找，最小的数就是这个位置应存的数，记住这两个数的位置，最后用题目所给的方法移动即可，类似于选择排序。

时间复杂度 $O(N^2)$。

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int T;
inline void solve() {
	string s;
	int n,a[505],bz[505];
	cin >> n; 
	
	for(int i = 1;i <= n; i++) {
		cin >> a[i];
	}
	
	int q[505][55],cnt = 0;
	
	for(int i = 1;i <= n; i++) {
		
		int mn = INT_MAX,mx; // mn 是最小的数，mx 是其位置 
		
		for(int j = i;j <= n; j++) {
			if(a[j] < mn) {
				mn = a[j];
				mx = j;
			} // 找最小的数 
		}
		
		if(mx == i) continue; //位置正确，不用移动 
		
		cnt++;
		q[cnt][1] = i,q[cnt][2] = mx,q[cnt][3] = mx - i; //记录 
		
		for(int j = mx;j > i; j--) {
			a[j] = a[j-1];
		} //移动 
		
		a[i] = mn;
		
	}
	
	cout << cnt << '\n';
	
	for(int i = 1;i <= cnt; i++) {
		cout << q[i][1] << ' ' << q[i][2] << ' ' << q[i][3] << '\n';
	}
}
int main() {
	cin >> T;
	
	while(T--) {
		solve();
	}
	
	return 0;
}
```

---

