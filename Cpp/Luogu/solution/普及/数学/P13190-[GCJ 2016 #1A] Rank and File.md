# [GCJ 2016 #1A] Rank and File

## 题目描述

当 Argus 军士的部队集合训练时，士兵们会站成一个 $\mathbf{N} \times \mathbf{N}$ 的正方形网格，每个格子里恰好有一名士兵。每位士兵都有一个确定的身高。

Argus 认为时刻关注每一位士兵非常重要。由于他喜欢从左上角观察整个方阵，他要求：

- 在每一行内，士兵的身高必须从左到右严格递增。
- 在每一列内，士兵的身高必须从上到下严格递增。

虽然同一行或同一列内不能有身高相同的士兵，但整个网格中可以有多名士兵身高相同。

由于士兵们有时会分别与自己所在的行或列进行训练，Argus 让你记录一份报告，内容包括 $2 \times \mathbf{N}$ 份士兵身高的列表：每一行（从左到右）和每一列（从上到下）各一份。当你巡视士兵时，你只能用很小的纸条记下每一份列表，因此每份列表都写在一张不同的纸条上。然而，在回办公室的路上，你被一声响亮的军号吓了一跳，所有纸条都掉在了地上，风把其中一张吹走了！剩下的纸条顺序已乱，你也不记得哪些是行、哪些是列，因为你没有记录这一点。

你知道，如果你交给 Argus 的报告不完整，他一定会让你做上百个俯卧撑。你能否找出缺失的那一份列表？


## 说明/提示

**样例解释**

在样例中，可能的方阵为：
```
1 2 3
2 3 4
3 5 6
```

或
```
1 2 3
2 3 5
3 4 6
```

无论哪种情况，缺失的列表都是 `3 4 6`。

**限制条件**

- $1 \leqslant \mathbf{T} \leqslant 50$。
- $1 \leqslant$ 所有身高 $\leqslant 2500$。
- 每行的整数均严格递增。
- 保证存在唯一的合法解。

**小数据集（14 分，测试集 1 - 可见）**

- $2 \leqslant \mathbf{N} \leqslant 10$。

**大数据集（21 分，测试集 2 - 隐藏）**

- $2 \leqslant \mathbf{N} \leqslant 50$。

翻译由 GPT4.1 完成。

## 样例 #1

### 输入

```
1
3
1 2 3
2 3 5
3 5 6
2 3 4
1 2 3```

### 输出

```
Case #1: 3 4 6```

# 题解

## 作者：Hkb150429 (赞：3)

## 题意

当 Argus 军士的部队集合训练时，士兵们会站成一个 $\mathbf{N} \times \mathbf{N}$ 的正方形网格，每个格子里恰好有一名士兵。每位士兵都有一个确定的身高。

由于士兵们有时会分别与自己所在的行或列进行训练，Argus 让你记录一份报告，内容包括 $2 \times \mathbf{N}$ 份士兵身高的列表：每一行（从左到右）和每一列（从上到下）各一份。但是收了一条报告。

## 思路

首先，统计数字个数，再收集奇数次数字，遍历数组，收集所有出现次数为奇数次的数字，这些数字即属于缺失的列表，最后输出就可以了。

## AC code

```
#include<bits/stdc++.h>
using namespace std;
int a[2505];
int t,n;
void chu(){
    for(int i=1;i<=2500;i++)a[i]=0;
}
int main() {
    cin>>t;
    for (int i=1;i<=t;i++) {
        cin>>n;
        chu();
        for (int j=1;j<=2*n-1;j++) {
            for (int k=1;k<=n;k++) {
                int num;
                cin>>num;
                a[num]++;
            }
        }
        cout<<"Case #"<<i<<": ";
        for(int j=1;j<=2500;j++){
            if(a[j]%2==1)cout<<j<<' ';
        }
        cout << endl;
    }
    return 0;
}
```

---

## 作者：Zjb13927701829 (赞：3)

# P13190 Rank and File 题解
[题目传送门](https://www.luogu.com.cn/problem/P13190)
## 看题
题目给我们一个 $N \times N$ 的方阵，满足：
- 在每一行内，士兵的身高必须从左到右**严格递增**。
- 在每一列内，士兵的身高必须从上到下**严格递增**。\
然后又有 $2 \times N$ 张小纸条，记录士兵每一行、每一列的身高。\
但是，这些小纸条的顺序不仅被打乱，还丢失了一张小纸条。题目让我们求的就是这张丢失的小纸条的内容。
## 解题思路
由于每一张小纸条都记录了士兵每一行、每一列的身高，所以每一个士兵的身高都会被统计 $2$ 次，每一个相同身高在小纸条上都会被统计 $2 \times x$ 次（$x$ 代表这个身高的人数）。\
那我们就能先用 map 统计每个身高出现的次数，然后遍历整个 map，看哪些身高出现的次数为**奇数**，这个就是丢失的小纸条上其中一个身高，最后排序即可。

话不多说，上代码！
## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;cin>>t;
    for(int i=1;i<=t;i++){
        int n,x;cin>>n;
        map<int,int>mp; //用map代替数组不会超时，vector也行
        for(int j=1;j<2*n;j++){
			for(int k=1;k<=n;k++){
				cin>>x;
				mp[x]++;
			}
        }
        int k[55],s=0;
		int zhi;
        for(auto zhi:mp){ //DevC++这里不知道为什么报错了，但洛谷可以
            if(zhi.second%2==1) s++,k[s]=zhi.first;
        }
        sort(k+1,k+s+1);//排序输出
        cout<<"Case #"<<i<<": "; 
        for(int j=1;j<=n;j++){
            cout<<k[j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}
```
`好了，今天的题解就到这里，感谢您的观看，我们下次再见！`

---

## 作者：zhongjunnan561234 (赞：1)

# 题意
当 Argus 军士的部队集合训练时，士兵们会站成一个 $N×N$ 的正方形网格，每个格子里恰好有一名士兵。每位士兵都有一个确定的身高。

因为士兵们有时会与自己所在的行或列进行训练，Argus 让你记录一份报告，内容包括 $2×N$ 份士兵身高的列表：每一行（从左到右）和每一列（从上到下）各一份。但是收了一条报告。
# 思路
首先，统计每个数字个数，再遍历数组，找到所有出现次数为奇数次的数字，最后输出就可以了。
# AC Code
为了维护社区安全，这里就不放代码了，按照上面的思路，很快就能做出来。~~而且也很简单~~

---

## 作者：Ashford (赞：1)

# 洛谷 P13190 [GCJ 2016 #1A] Rank and File C++ 题解

## 解题思路

本题的核心思路：方阵中元素出现次数的规律

- 在完整的 $N \times N$ 方阵中，共有 $2N$ 个列表（$N$ 行和 $N$ 列），每个元素既属于某一行也属于某一列，因此会在所有列表中出现 **2 次**。
- 当丢失一个列表后，该列表中的所有元素在剩余的 $2N-1$ 个列表中只会出现 **1 次**（奇数次），而其他元素仍然保持 **2 次** 出现（偶数次）。

因此，我们只需统计所有元素的出现次数，筛选出奇数次出现的元素并排序，即可得到缺失的列表。

## C++代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    for (int c = 1; c <= t; ++c) {
        int n;
        cin >> n;
        map<int, int> cnt;  // 计数：元素 -> 出现次数
        
        // 读取所有元素并计数
        int total = (2 * n - 1) * n;
        for (int i = 0; i < total; ++i) {
            int x;
            cin >> x;
            cnt[x]++;
        }
        
        // 收集出现奇数次的元素
        vector<int> res;
        for (auto& p : cnt) {
            if (p.second % 2 == 1) {
                res.push_back(p.first);
            }
        }
        
        // 排序并输出
        sort(res.begin(), res.end());
        cout << "Case #" << c << ": ";
        for (int i = 0; i < res.size(); ++i) {
            if (i > 0) cout << " ";
            cout << res[i];
        }
        cout << endl;
    }
    return 0;
}

```

## 时间复杂度分析

- **时间复杂度**：$O(T \cdot N^2 \log N)$
- **空间复杂度**：$O(N^2)$

---

## 作者：cyz1234 (赞：0)

# P13190 [GCJ 2016 #1A] Rank and File题解
## 题意
有一个 $N\times N$ 的军队，每一个士兵都有他自己的身高，若第 $i$ 行第 $j$ 列的士兵身高为 $a_{i,j}$，则有 $a_{i,j}<a_{i,j+1}$ 和 $a_{i,j}<a_{i+1,j}$。

我们有 $2\times N-1$ 个纸条，记录着每一行与每一列的士兵的身高，可我们有一张纸条不见了，我们需要求丢失的纸条的内容。
## 思路
已知我们的纸条记录着每一行与每一列的士兵的身高，为 $a_{i,j}$ 的士兵的身高都会出现在第 $i$ 行与第 $j$ 列所记录的纸条上。

综上所述，我们只需要记录士兵身高出现次数，如果为 $a_{i,j}$ 的士兵身高出现次数为奇数，则他的身高就在丢失的纸条上，又因为 $a_{i,j}<a_{i,j+1}$ 且 $a_{i,j}<a_{i+1,j}$，所以答案的身高为一个严格递增序列。
## 奉上AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5005;
int t;//测试数据个数
int main(){
	cin>>t;
	for(int i=1;i<=t;i++){
		int a[N]={};//记录身高出现次数的数组
		int n,x;
		cin>>n;
		for(int j=1;j<=2*n-1;j++){
			for(int k=1;k<=n;k++){
				cin>>x;
				a[x]++;//记录此身高的出现个数
			}
		}
		cout<<"Case #"<<i<<":";
		for(int j=1;j<=2500;j++){
			if(a[j]&1){//如果士兵身高出现次数为奇数
				cout<<" "<<j;//则他的身高就在丢失的纸条上
			}
		}
		cout<<endl;//别忘了换行
	}
	return 0;//华丽结束
}
```

---

## 作者：Velya_QiDream (赞：0)

## 解题思路
由于网格的每行和每列都是**严格递增**的，对于网格中的元素，除了一些特殊情况（比如最后一行、最后一列的部分元素），大部分元素会在“行列表”和“列列表”中**各出现一次**，也就是总共出现两次。

而在缺失了一个列表后，这个列表里的所有元素，其在所有剩余列表中的出现次数都会比正常情况少一次，即出现**奇数次**（正常是偶数次，少一次就变为奇数次）。

所以我们只要统计所有元素的出现次数，然后选出**奇数次**出现的元素并排序，就可以得到缺失的列表。

## 代码
```c++
#include <bits/stdc++.h>
using namespace std;

const int tt=110;
int k[tt];

int main(){
    int t;
	cin >>t;
    for(int i=1;i<=t;i++){
        int n;
		cin >>n;
		map<int,int> mp;
		memset(k,0,sizeof k);
        for(int j=1;j<2*n;j++){
			for(int k=1;k<=n;k++){
				int x;
				cin >>x;
				mp[x]++;
			}
        }
        int idx=0;
        for(auto it:mp){
            if(it.second%2==1){
            	idx++;
            	k[idx]=it.first;
			}
        }
        sort(k+1,k+1+idx);
        cout <<"Case #"<<i<<": "; 
        for(int j=1;j<=n;j++){
            cout <<k[j]<<" ";
        }
        cout <<endl;
    }
    return 0;
}
```

---

## 作者：Nahia (赞：0)

### 思路

由于每个士兵的身高一定在他所在的行和列各出现一次，所以如果列表完整，那么每个士兵必定出现偶数次，易得每个身高必定出现偶数次。不难想到出现奇数次的身高一定是那一行或者那一列的列表缺失了，按升序输出这些士兵的身高即可。

### solution

```cpp line-numbers
#include<bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
#define For(i,a,b) for(int i = a;i<=b;i++)
#define Rof(i,a,b) for(int i = a;i>=b;i--)
using namespace std;
inline __int128 read(){__int128 x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-'){f=-1;}c=getchar();}while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}return f*x;}
inline void write(__int128 x){if(x<0){putchar('-');x=-x;}if(x>9)write(x/10);putchar(x%10+'0');}
int a[2505];
int main(){
	int t = read();
	For(id,1,t){
		int n = read(),mx = -1;
		set<int> st;
		memset(a,0,sizeof(a));
		For(i,1,2*n-1){
			For(j,1,n){
				int x = read();
				mx = max(mx,x);
				a[x]++;
			}
		}
		For(i,1,mx){
			if(a[i]%2==1){
				st.insert(i);
			}
		}
		printf("Case #%d: ",id);
		for(auto it:st){
			write(it);
			putchar(' '); 
		}
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：koukou (赞：0)

一道简单的数学题，建议降橙。

对于一个身高士兵，他必然会在当前行和当前列各出现一次，也就是出现次数为偶数，如果有多个士兵的身高相同呢？很显然，出现次数也为偶数。\
所有只需要统计所有身高的出现次数，最后找到所有出现次数为奇数的身高，最后统一输出即可。

代码:
```
#include<bits/stdc++.h>
using namespace std;
const int N = 50 + 1;
const int M = 25e2 + 1; 
int T, n, mp[M];
int main()
{
	cin >> T;
	for(int id = 1; id <= T; id++)
	{
		cin >> n;
		memset(mp, 0, sizeof(mp));//清空统计数组
		for(int i = 1; i < 2 * n; i++)
		{
			for(int j = 1; j <= n; j++)
			{
				int x;
				cin >> x; 
				mp[x]++;//出现了一次该身高
			}
		}
		cout << "Case #" << id << ": ";
		for(int i = 1; i < M; i++)
		{
			if(mp[i] % 2 == 1) cout << i << " ";//缺失的身高
		}
		cout << "\n";
	}
    return 0;
}
```

---

## 作者：NeiKos496_Phainon (赞：0)

第一眼，枚举，感觉很慌；第二眼，严格递增+保证有解，于是想到了一种~~投机的~~办法  
# 题目大意  
有一个$N \times N$的矩阵，其中每一行每一列都是严格递增。将每一行和每一列写在纸条上并打乱顺序，其中有一行或一列被删了，让你找出不见的纸条。  
# 思路  
毕竟是行和列都给出来了，所以每一个数字的出现的次数都是2的倍数。至于那些没出现的，就是在被删除的纸条上，所以用桶存储+排序输出即可。
# 代码  
```cpp
#include<bits/stdc++.h>
using namespace std;
bool a[2507];
int main() {
	int t;
	cin >> t;
	for (int i = 1; i <= t; i++) {
		memset(a, 0, sizeof(a));
		int n;
		cin >> n;
		for (int j = 1; j <= n * n * 2 - n; j++) {
			int x;
			cin >> x;
			a[x] = 1 - a[x];
		}
		cout << "Case #" << i << ":";
		for (int j = 1; j <= 2500; j++) {
			if (a[j]) cout << " " << j;
		}
		cout << endl;
	}
	return 0;
}
```

---

## 作者：lijingshu_304775 (赞：0)

题目链接：<https://www.luogu.com.cn/problem/P13190>。

## 分析

题意：给定一个 $N \times N$ 的网格，每行和每列的士兵身高严格递增。现在丢失了一行或一列，剩下 $2 \times N-1$ 个列表。要求找出缺失的那一行或列。

首先我们可以统计所有数字的出现次数（每个数字在行列中出现的总次数应该是偶数，除非它属于缺失的那一行或一列）。

然后筛选奇数次出现的数字（缺失的行或列中的每个数字出现次数为奇数）。

最后排序输出（将这些数字排序后即为缺失的行或列）。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int cnt[2505];// 统计每个身高的出现次数
int m[55];// 存储缺失的行/列
int main() {
	int t;
	cin >> t;
	for (int c = 1; c <= t; c++) {//用于输出行号
		int n;
		cin >> n;
		memset(cnt, 0, sizeof(cnt));//清空
		for (int i = 0; i < 2 * n - 1; i++) {
			for (int j = 0; j < n; j++) {
				int x;
				cin >> x;
				cnt[x]++;
			}
		}
		// 收集出现奇数次的身高
		memset(m, 0, sizeof(m));//清空
		int k = 0; 
		for (int i = 1; i < 2505; i++) {
			if (cnt[i] % 2) m[k++] = i;
		}
		sort(m, m + k);
		printf("Case #%d:", c);
		for (int i = 0; i < k; i++) {
			printf(" %d", m[i]);
		}
		cout << endl;
	}
	return 0;
}
```

注意事项：

1. 不要学我把 `cin`，`cout` 和 `scanf`，`printf` 混用，虽然这样你可能也会 A 了这道题，但这也是不好的习惯。

2. 因为有 $T$ 组测试用例，所以每次处理要清空。

---

