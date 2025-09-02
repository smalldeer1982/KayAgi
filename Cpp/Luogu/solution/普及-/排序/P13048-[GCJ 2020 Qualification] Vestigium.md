# [GCJ 2020 Qualification] Vestigium

## 题目描述

Vestigium 在拉丁语中意为“痕迹”。本题中，我们将研究拉丁方阵与矩阵的迹。

一个方阵的迹是指其主对角线上所有元素的和（主对角线从左上角延伸至右下角）。

一个 $N \times N$ 的方阵被称为**拉丁方阵**，当且仅当每个单元格包含 $N$ 个不同的值，且每一行和每一列中都没有重复的值。在本题中，我们仅讨论“自然拉丁方阵”，即这些 $N$ 个值为 $1$ 到 $N$ 之间的整数。

给定一个仅包含 $1$ 到 $N$ 之间整数的矩阵，我们需要计算其迹，并检查它是否是一个自然拉丁方阵。为了提供更多信息，除了简单地告诉我们矩阵是否为自然拉丁方阵外，请计算包含重复值的行数和列数。

## 说明/提示

**样例解释**

在样例一中，输入是一个自然拉丁方阵，因此没有任何行或列包含重复元素。主对角线上的四个值均为 $1$，因此迹（它们的和）为 $4$。

在样例二中，所有行和列均包含重复元素。注意，无论重复元素的数量或重复次数如何，每行或每列仅被计数一次。此外，$1$ 到 $N$ 之间的某些整数可能在输入中缺失。

在样例三中，最左和最右的列包含重复元素。

**数据范围**

**测试集 $1$（$7$ 分，可见判定）**

- $1 \leq T \leq 100$。
- $2 \leq N \leq 100$。
- 对于所有 $i, j$，$1 \leq M_{i,j} \leq N$。

翻译由 DeepSeek V3 完成。

## 样例 #1

### 输入

```
3
4
1 2 3 4
2 1 4 3
3 4 1 2
4 3 2 1
4
2 2 2 2
2 3 2 3
2 2 2 3
2 2 2 2
3
2 1 3
1 3 2
1 2 3```

### 输出

```
Case #1: 4 0 0
Case #2: 9 4 4
Case #3: 8 0 2```

# 题解

## 作者：ARIS1_0 (赞：3)

很简单的一道题。

## 题意

给出一个 $n\times n$ 大小的正整数矩阵，你需要求出：矩阵从左上角到右下角对角线上所有元素的和，矩阵中有多少个含有重复元素的行和列。多测。

数据范围：$1\le T\le 100,2\le n\le 100$，单个元素不超过 $n$。

## 思路

扫描单行和单列是 $O(n)$ 的，故扫描整个矩阵是 $O(n^2)$ 的，纯模拟的总复杂度也就 $O(Tn^2)$，总计算量在 $10^6$ 左右，故纯模拟就可以通过本题。

具体地，我们开一个桶数组 $vis$，记录在单行或单列中一个元素是否出现过。若我们遍历到了一个元素，且该元素对应的 $vis_{a_{i,j}}$ 的值不为 $0$，则表示该元素已经在该行或该列中出现过。那么我们的答案就会增加。

## 代码


```cpp
//其中 read 函数是快速读入函数
int n,mp[105][105];
inline void work(int id){
	n=read();
	int cnt1=0,cnt2=0,sum=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)mp[i][j]=read();
	}
	for(int i=1;i<=n;i++)sum+=mp[i][i];//求对角线之和
	bitset<105>vis;
	for(int i=1;i<=n;i++){//行
		vis.reset();//每次遍历时记得清空桶
		bool f=0;
		for(int j=1;j<=n;j++){
			f|=vis[mp[i][j]];
			vis[mp[i][j]]=1;
		}
		cnt1+=f;
	}
	for(int j=1;j<=n;j++){//i 和 j 反过来枚举就变成了列
		vis.reset();
		bool f=0;
		for(int i=1;i<=n;i++){
			f|=vis[mp[i][j]];
			vis[mp[i][j]]=1;
		}
		cnt2+=f;
	}
	printf("Case #%d: %d %d %d\n",id,sum,cnt1,cnt2);
}
int t;
int main(){
	t=read();
	for(int i=1;i<=t;i++)work(i);
	return 0;
}
```

---

## 作者：__szh_DNCB__ (赞：2)

本蒟蒻的第三篇题解。

简单模拟。

本题要求算出 $k$ 和 $r$ 和 $c$ 三个数，其中 $k$ 最简单，直接从左上到右下搜索相加即可。

$r$ 和 $c$ 计算方法类似，因为题目规定 $1 \le M_{i,j} \le N \le 100$，所以开一个容量为 $105$ 的桶即可。

注意到计算 $c$ 时可以使外层循环自变量为 $j$，内层的为 $i$，这样可以保持调用数组时依然是 $M_{i,j}$ 的形式。

注意输出格式，这题能用还是用 `printf` 输出，像我这样纯用 `cout` 输出的人的输出会很长且容易出错。

代码如下。

```cpp
#include<bits/stdc++.h>
using namespace std;
int s[105][105];
void solve(int time){
	memset(s,0,sizeof s);
	int n;
	cin >> n;
	int k=0,r=0,c=0;
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++){
			cin >> s[i][j];
		}
	}
	for (int i=1;i<=n;i++){
		k += s[i][i];
	}
	for (int i=1;i<=n;i++){
		int cnt[105] = {};
		for (int j=1;j<=n;j++){
			if (cnt[s[i][j]] == 1){
				r++;
				break;
			}
			else cnt[s[i][j]]++;
		}
	}
	for (int j=1;j<=n;j++){
		int cnt[105] = {};
		for (int i=1;i<=n;i++){
			if (cnt[s[i][j]] == 1){
				c++;
				break;
			}
			else cnt[s[i][j]]++;
		}
	}
	cout << "Case #" << time << ": ";
	cout << k << ' ' << r << ' ' << c << '\n';
}
int main(){
	int T;
	cin >> T;
	for (int i=1;i<=T;i++){
		solve(i);
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/P13048#ide)

这是一道比较简单的**矩阵处理与统计**的题目。
### 前言  
这道题目要求我们对给定的矩阵进行三个方面的检查：首先计算矩阵的迹（即主对角线元素的和），然后统计包含重复元素的行数，最后统计包含重复元素的列数。题目中的矩阵可能包含 $1$ 到 $N$ 之间的整数，我们需要判断它是否是一个自然拉丁方阵，并提供相关的统计信息。

### 思路  
我们可以通过遍历矩阵来解决这个问题。首先计算主对角线元素的和作为矩阵的迹。然后检查每一行是否有重复元素，使用集合来快速判断重复。同样的方法也适用于检查每一列。统计有重复的行数和列数，最终按照要求的格式输出结果。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        int N;
        cin >> N;
        int m[N][N];
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                cin >> m[i][j];
        int t1 = 0, rd = 0, c = 0;
        for (int i = 0; i < N; i++) t1 += m[i][i];
        for (int i = 0; i < N; i++) {
            unordered_set<int> s;
            for (int j = 0; j < N; j++) s.insert(m[i][j]);
            if (s.size() != N) rd++;
        }

        for (int j = 0; j < N; j++) {
            unordered_set<int> s;
            for (int i = 0; i < N; i++) s.insert(m[i][j]);
            if (s.size() != N) c++;
        }

        cout << "Case #" << t << ": " << t1 << " " << rd << " " << c << "\n";
    }
    return 0;
}
```

---

## 作者：_WCW_ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P13048)
## 题目分析
这道题其实就是求一个 $N \times N$ 的矩阵的主对角线的元素之和，同时求出矩阵中有多少个含有重复元素的行和列。
## 解题思路
求主对角线元素之和比较好求，重点在于如何计算有多少个含有重复元素的行和列。我们可以利用 ```set``` 容器自动去重的性质，将每一行或每一列的元素存入容器中，如果容器的长度比 $N$ 小，说明有元素被去重了（举个例子，例如 $N$ 是 $5$，而某一行中有 $3$ 个元素是重复的，存入 ```set``` 中，重复的元素只会被存入一次，所以这个容器的长度会比 $N$ 小），这时计数变量加一，最后输出即可。
## [AC](https://www.luogu.com.cn/record/222247109) 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,m[110][110];//m用于存储数据
int main()
{
    scanf("%d",&t);//输入t
    for(int cnt=1;cnt<=t;cnt++)//循环t次
    {
        int k=0,r=0,c=0;//这些变量均为题中意思，初始化为0
        scanf("%d",&n);//输入n
        memset(m,0,sizeof(m));//保险起见将m数组全部设为0
        for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) scanf("%d",&m[i][j]);//输入矩阵
        for(int i=1,j=1;i<=n && j<=n;i++,j++) k+=m[i][j];//计算主对角线元素之和，主对角线上的元素行和列是一样的
        for(int i=1;i<=n;i++)//循环每一行，计算有重复元素的行
        {
            set<int> a;//set容器
            for(int j=1;j<=n;j++)//循环每一列
            {
                a.insert(m[i][j]);//将每个元素放入set中
            }
            if(a.size()<n) r++;//如果有重复元素，计算重复行的计数变量加一
        }
        for(int i=1;i<=n;i++)//循环每一列，计算有重复元素的列
        {
            set<int> a;//set容器
            for(int j=1;j<=n;j++)//循环每一行
            {
                a.insert(m[j][i]);//将每个元素放入set中
            }
            if(a.size()<n) c++;//如果有重复元素，计算重复列的计数变量加一
        }
        printf("Case #%d: %d %d %d\n",cnt,k,r,c);//按照题目格式输出
    }

    return 0;
}
```

---

## 作者：XsIeEiKcEk (赞：1)

~~时间限制有点离谱。~~

### 解法

首先，我们可以发现“迹”要加的位置的横纵坐标相等，即迹为 $\sum_{i=1}^{N}M_{i,i}$。

至于记录重复的行与列，我们可以直接 $O(N^3)$ 暴力查找。先遍历每一行或列，再在那一行或列 $O(N^2)$ 判断每一个元素是否与其他元素相等，最后输出。

### CODE
```cpp
//实际上有很多可以剪枝的地方，但作者太懒了
#include <iostream>
using namespace std;
int t, num = 0;

int main() {
	cin >> t;
	while (t--) {
		int n, a[101][101];
		cin >> n;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				cin >> a[i][j];
		cout << "Case #" << ++num << ": ";
		int ji = 0;
		for (int i = 1; i <= n; i++)//记录“迹”
			ji += a[i][i];
		cout << ji << ' ';
		int hang_CF = 0;
		for (int i = 1; i <= n; i++) {
			bool chongfu = 0;
			for (int j = 1; j <= n; j++)
				for (int k = 1; k <= n; k++)
					if (a[i][j] == a[i][k] && j != k)//j与k不能相等
						chongfu = 1;
			if (chongfu)
				hang_CF++;
		}
		cout << hang_CF << ' ';
		int lie_CF = 0;
		for (int i = 1; i <= n; i++) {
			bool chongfu = 0;
			for (int j = 1; j <= n; j++)
				for (int k = 1; k <= n; k++)
					if (a[j][i] == a[k][i] && j != k)//同前
						chongfu = 1;
			if (chongfu)
				lie_CF++;
		}
		cout << lie_CF << '\n';
	}
	return 0;
}
```

---

## 作者：bz029 (赞：0)

### 思路
由题面知，此题为模拟题。只需按题意模拟即可。

设第 $i$ 行，第 $j$ 列的数表示为 $a_{i,j}$；第 $i$ 个询问的答案为 $sum_i$；计数数组 $b_i$，表示在此行（列）出现了 $b_i$ 次 $i$。

对于第 $1$ 个询问，只需将满足条件 $i=j$，即可将 $sum_1$ 加上 $a_{i,j}$。

对于第 $2$ 个询问，只需遍历每一行，将这行所出现的 $b_{a_{i,j}}$ 加上 $1$，再统计是否有某一个数出现次数大于 $2$ 次，即满足 $1\le i\le N$ 且 $2\le b_i$ 即可将 $sum_2$ 加上 $1$。

对于第 $3$ 个询问，与第 $2$ 个询问同理，改成遍历每一列即可。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+5;

int t,n,a[N][N],b[N];

int main(){
	cin>>t;
	for(int o=1;o<=t;o++){
		int sum1=0,sum2=0,sum3=0;//局域变量要清零 
		cin>>n;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				cin>>a[i][j];
				if(i==j) sum1+=a[i][j];//统计sum1 
			}
		}
		//统计sum2 
		for(int i=1;i<=n;i++){
			bool f=0;
			for(int j=1;j<=n;j++) b[j]=0;
			for(int j=1;j<=n;j++){
				b[a[i][j]]++;
				if(b[a[i][j]]>1){
					f=1;
					break;
				}
			}
			if(f) sum2++;
		}
		//统计sum3
		for(int i=1;i<=n;i++){
			bool f=0;
			for(int j=1;j<=n;j++) b[j]=0;
			for(int j=1;j<=n;j++){
				b[a[j][i]]++;
				if(b[a[j][i]]>1){
					f=1;
					break;
				}
			}
			if(f) sum3++;
		}
		printf("Case #%d: %d %d %d\n",o,sum1,sum2,sum3);//要按格式输出 
	}
		
	return 0;
}
```

---

## 作者：zhunxin666 (赞：0)

一篇模拟，直接按照题意模拟即可，有求下面的三项：
- 求出方阵左上角到右下角的和。
- 看看有多少行中的数是重复的。
- 看看有多少列中的数是重复的。

#### 注意：无论重复元素的数量或重复次数如何，每行或每列仅被计数一次。

```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,a[105][105],cnt;
void solve(){
	cin>>n;
	cnt++;//当前第几轮，方便后面输出 
	int ans=0,r=0,c=0;//多测清空 
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>a[i][j];//输入 
			if(i==j) ans+=a[i][j];//如果是对角线,那么答案加上 
		}
	}
	for(int i=1;i<=n;i++){//行的情况 
		map <int,int> m;//统计有没有重复的数 
		for(int j=1;j<=n;j++){
			if(m.find(a[i][j])!=m.end()){r++;break;}//如果已经有重复的元素，就答案++,推出循环,防止多加了答案 
			m[a[i][j]]++;//没有就添加 
		}
	}
	for(int i=1;i<=n;i++){//与上面同理,只不过这次是列 
		map <int,int> m;
		for(int j=1;j<=n;j++){
			if(m.find(a[j][i])!=m.end()){c++;break;}
			m[a[j][i]]++;
		}
	}
	cout<<"Case #"<<cnt<<": "<<ans<<" "<<r<<" "<<c<<endl;//注意格式 
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--) solve();//多测调用函数 
	return 0;
}

```

---

## 作者：wjh27465 (赞：0)

# 题解：P13048 [GCJ 2020 Qualification] Vestigium
## 分析
首先观察到时限竟然有 $20$ 秒！暴力搞肯定也不会超时。  
定义一个二维数组，重复 $t$ 次读入 $n \times n$ 的矩阵，随后依次开始判断。对角线上的数字的两个下标相同，将其累加进 $k$ 中。  
计算重复元素的行数时，可以开 $3$ 层循环。第一层循环枚举行，第二层和第三层循环判断这一行中是否有重复元素。注意发现重复元素后记得要把第二层和第三层循环结束掉。同样的，计算重复元素的列数时，只需将数组的两个下标位置换一下即可。  
最后依次输出 $k,r,c$ 的值。
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int a[105][105];
int main()
{
    int t;
    cin>>t;
    for(int i=1;i<=t;i++)
    {
        int n,k=0,r=0,c=0;
        cin>>n;
        for(int j=1;j<=n;j++)
        {
            for(int l=1;l<=n;l++)
                cin>>a[j][l];
        }
        for(int j=1;j<=n;j++)
            k+=a[j][j];
        for(int j=1;j<=n;j++)
        {
            int f=0;
            for(int l=1;l<n;l++)
            {
                if(f)
                    break;
                for(int m=l+1;m<=n;m++)
                {
                    if(f)
                        break;
                    if(a[j][l]==a[j][m])
                    {
                        r++;
                        f=1;
                    }
                }
            }
        }
        for(int j=1;j<=n;j++)
        {
            int f=0;
            for(int l=1;l<n;l++)
            {
                if(f)
                    break;
                for(int m=l+1;m<=n;m++)
                {
                    if(f)
                        break;
                    if(a[l][j]==a[m][j])
                    {
                        c++;
                        f=1;
                    }
                }
            }
        }
        cout<<"Case #"<<i<<": "<<k<<" "<<r<<" "<<c<<endl;
    }
    return 0;
}
```

---

## 作者：goIdie (赞：0)

## 思路

按题意模拟即可。

先求出矩阵从左上到右下的对角线的和。再遍历两次矩阵，分别求出矩阵有重复数字的行和列的个数。

代码细节比较多，注意多测清空。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a[101][101],ans1,ans2,ans3;
bool f;
map<int,int>mp; 
int main(){ 
    cin>>T;
    for(int t=1;t<=T;t++){
    	ans1=ans2=ans3=0;
    	f=0;
    	mp.clear();
        cin>>n;
        for(int i=1;i<=n;i++){
        	for(int j=1;j<=n;j++){
        		cin>>a[i][j];
			}
		}
		for(int i=1;i<=n;i++){
			ans1+=a[i][i];
		}//求对角线的和
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(mp[a[i][j]]){
					f=1;
					break;
				}
				else{
					mp[a[i][j]]=1;
				}
			}
			if(f){
				ans2++;
			}
			mp.clear();
			f=0;
		}//计算有重复数字的行数
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(mp[a[j][i]]){
					f=1;
					break;
				}
				else{
					mp[a[j][i]]=1;
				}
			}
			if(f){
				ans3++;
			}
			mp.clear();
			f=0;
		}//计算有重复数字的列数
        cout<<"Case #"<<t<<": "<<ans1<<" "<<ans2<<" "<<ans3<<endl;
    }
    return 0;
}
```

---

