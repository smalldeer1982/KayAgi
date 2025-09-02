# [ABC319C] False Hope

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc319/tasks/abc319_c

$ 3\times3 $ のマス目に $ 1 $ から $ 9 $ までの数字が書き込まれており、上から $ i $ 行目、左から $ j $ 列目 $ (1\leq\ i\leq3,1\leq\ j\leq3) $ に書き込まれている数字は $ c\ _\ {i,j} $ です。

異なるマスに同じ数字が書き込まれている場合もありますが、同じ数字が縦・横・斜めに $ 3 $ つ連続して書き込まれていることはありません。 より厳密には、$ c\ _\ {i,j} $ について次の条件のすべてが成り立っていることが保証されます。

- どの $ 1\leq\ i\leq3 $ についても、$ c\ _\ {i,1}=c\ _\ {i,2}=c\ _\ {i,3} $ ではない
- どの $ 1\leq\ j\leq3 $ についても、$ c\ _\ {1,j}=c\ _\ {2,j}=c\ _\ {3,j} $ ではない
- $ c\ _\ {1,1}=c\ _\ {2,2}=c\ _\ {3,3} $ ではない
- $ c\ _\ {3,1}=c\ _\ {2,2}=c\ _\ {1,3} $ ではない
 
高橋くんは、それぞれのマスに書かれている数字をランダムな順番で知ります。 高橋くんは、縦・横・斜めの列のうちの $ 1 $ つでも次の条件を満たしたとき**がっかり**します。

- はじめに知ったほうの $ 2 $ マスに書かれた数字が同じであり、最後に知ったマスに書かれた数字がそれと異なる。
 
高橋くんががっかりせずにすべてのマスに書かれた数字を知る確率を求めてください。

## 说明/提示

### 制約

- $ c\ _\ {i,j}\in\lbrace1,2,3,4,5,6,7,8,9\rbrace\ (1\leq\ i\leq3,1\leq\ j\leq3) $
- $ c\ _\ {i,1}=c\ _\ {i,2}=c\ _\ {i,3} $ ではない $ (1\leq\ i\leq3) $
- $ c\ _\ {1,j}=c\ _\ {2,j}=c\ _\ {3,j} $ ではない $ (1\leq\ j\leq3) $
- $ c\ _\ {1,1}=c\ _\ {2,2}=c\ _\ {3,3} $ ではない
- $ c\ _\ {1,3}=c\ _\ {2,2}=c\ _\ {3,1} $ ではない
 
### Sample Explanation 1

例えば、高橋くんが $ c\ _\ {3,1}=2,c\ _\ {2,1}=2,c\ _\ {1,1}=3 $ の順に知った場合、高橋くんはがっかりしてしまいます。 !\[\](https://img.atcoder.jp/abc319/d4635a227bbb8db7143f4bbee77a9979.png) 対して、高橋くんが $ c\ _\ {1,1},c\ _\ {1,2},c\ _\ {1,3},c\ _\ {2,1},c\ _\ {2,2},c\ _\ {2,3},c\ _\ {3,1},c\ _\ {3,2},c\ _\ {3,3} $ の順に数字を知った場合、がっかりすることなくすべての数字を知ることができます。 高橋くんががっかりすることなくすべての数字を知ることができる確率は $ \dfrac\ 23 $ です。 絶対誤差が $ 10\ ^\ {-8} $ 以下であれば正答と判定されるため、$ 0.666666657 $ や $ 0.666666676 $ のように出力しても正解になります。

## 样例 #1

### 输入

```
3 1 9
2 5 6
2 7 1```

### 输出

```
0.666666666666666666666666666667```

## 样例 #2

### 输入

```
7 7 6
8 6 8
7 7 6```

### 输出

```
0.004982363315696649029982363316```

## 样例 #3

### 输入

```
3 6 7
1 9 7
5 7 5```

### 输出

```
0.4```

# 题解

## 作者：joe_zxq (赞：7)

# 思路

将 $9$ 个方格分别编号为 $1 \sim 9$。用 next_permutation 枚举每一种顺序，用 $ans$ 记录 Takahashi 高兴的方案数。

最后答案为 $\frac{ans}{9!=362880}$，注意保留小数！

时间复杂度：$O(9!)$。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[20],p[20],b[20];
bool check(int x,int y,int z){
	if(a[x]==a[y]&&((b[x]<b[y]&&b[y]<b[z])||(b[y]<b[x]&&b[x]<b[z])))return 0;
	if(a[x]==a[z]&&((b[x]<b[z]&&b[z]<b[y])||(b[z]<b[x]&&b[x]<b[y])))return 0;
	if(a[y]==a[z]&&((b[y]<b[z]&&b[z]<b[x])||(b[z]<b[y]&&b[y]<b[x])))return 0;
	return 1;
}
void solve(){
	for(int i=1;i<=9;i++)cin>>a[i];
	for(int i=1;i<=9;i++){
		p[i]=i;
	}
	int ans=0;
	do{
            for(int i=1;i<=9;i++){
        	b[p[i]]=i;
	    }
		if(check(1,4,7)&&check(2,5,8)&&check(3,6,9)&&check(1,2,3)&&check(4,5,6)&&check(7,8,9)&&check(1,5,9)&&check(3,5,7)){
			ans++;
		}
	}while(next_permutation(p+1,p+10));
	int tot=362880;
	cout<<fixed<<setprecision(10)<<(long double)(ans)/(long double)(tot);
}
int main(){
	int tc=1;
    while(tc--)solve();
    return 0;
} 
```

---

## 作者：_zzzzzzy_ (赞：4)

# 思路

发现可以用搜索搜出来全部不沮丧的个数，然后除上个数，这里因为数量是固定的那么除的就会是 $9!$。

最后说句闲话感觉这个题的难度在于读题。。。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
int mp[3][3], a[3][3];
double cnt;
void check() {
    bool flg = 0;
    for (int i = 0; i < 3; i++){
        if (mp[i][0] == mp[i][1] && a[i][0] < a[i][2] && a[i][1] < a[i][2]) {
            flg = 1;
        } if (mp[i][1] == mp[i][2] && a[i][1] < a[i][0] && a[i][2] < a[i][0]) {
            flg = 1;
        } if (mp[i][2] == mp[i][0] && a[i][2] < a[i][1] && a[i][0] < a[i][1]) {
            flg = 1;
        }
        if (mp[0][i] == mp[1][i] && a[0][i] < a[2][i] && a[1][i] < a[2][i]) {
            flg = 1;
        } if (mp[1][i] == mp[2][i] && a[1][i] < a[0][i] && a[2][i] < a[0][i]) {
            flg = 1;
        } if (mp[2][i] == mp[0][i] && a[2][i] < a[1][i] && a[0][i] < a[1][i]) {
            flg = 1;
        }
    }
    if (mp[0][0] == mp[1][1] && a[0][0] < a[2][2] && a[1][1] < a[2][2]) {
        flg = 1;
    }
    if (mp[1][1] == mp[2][2] && a[1][1] < a[0][0] && a[2][2] < a[0][0]) {
        flg = 1;
    }
    if (mp[2][2] == mp[0][0] && a[2][2] < a[1][1] && a[0][0] < a[1][1]) {
        flg = 1;
    }
    if (mp[0][2] == mp[1][1] && a[0][2] < a[2][0] && a[1][1] < a[2][0]) {
        flg = 1;
    }
    if (mp[1][1] == mp[2][0] && a[1][1] < a[0][2] && a[2][0] < a[0][2]) {
        flg = 1;
    }
    if (mp[2][0] == mp[0][2] && a[2][0] < a[1][1] && a[0][2] < a[1][1]) {
        flg = 1;
    }
    if (flg == 0) {
        cnt++;
    }
}
void dfs(int p){
    if (p == 10){
        check();
        return ;
    }
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (a[i][j] == 0){
                a[i][j] = p;
                dfs(p + 1);
                a[i][j] = 0;
            }
        }
    }
}
int main(){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            cin >> mp[i][j];
        }
    }
    dfs(1);
    cout << setprecision(10) << cnt / 362880 << "\n";
    return 0;
}
```

---

## 作者：tder (赞：3)

[$\Large\color{black}\textbf{AT\_abc319\_c False Hope}$](https://www.luogu.com.cn/problem/AT_abc319_c) $\Large\textbf{题解}$

[$\textbf{题目传送门}$](https://www.luogu.com.cn/problem/AT_abc319_c)

[$\textbf{更好的阅读体验}$](https://www.luogu.com.cn/blog/tder/solution-AT-abc319-c)

~~枚举 + 判断 + 概率~~

---

$$\large\textbf{题意}$$

给出一个 $3$ 行 $3$ 列的表格，每个格子均为 $1$ 到 $9$ 的数字之一。

相同数字可能出现多次，但保证同一行、同一列、同一对角线都不会出现 $3$ 个数字都相同的情况。

小明按任意随机顺序依次打开这 $9$ 个格子，如果出现以下情况，他会不满意：

- 在同一行或同一列或同一对角线上，他先看到的两个数字相同，而最后看到的那个数字与之不同。

请计算小明所有随机顺序查看方案中，感到满意的可能性概率。

特别注意：答案是浮点数，且只要和标准答案的绝对误差小于等于 $10^{-8}$ 就算正确。

---

$$\large\textbf{思路}$$

考虑枚举每一种打开的顺序，计 $h_{i,j}$ 表示 $(i,j)$ 位置上的格子打开的次序。下面的例子表示依次打开打开 $(1,2),(2,3),(1,1),\dotsm,(1,3)$ 位置上的格子。

```
3 1 9
8 5 2
6 7 4
```

枚举每一行、每一列、每一对角线，判断先打开的 $2$ 格中的数字是否相等。由于保证 $3$ 个格子不都相等，所以若先打开的 $2$ 格中的数字相等即不满意。若所有先打开的 $2$ 格均不相等，则满足条件，计数器 $cnt$ 累加即可。

最后输出 $\dfrac{cnt}{9!}$ 保留 $8$ 位小数的结果即可。

---

$$\large\textbf{代码}$$

```cpp
#include<bits/stdc++.h>
using namespace std;
int cnt, a[4][4], h[4][4];
bool check() { // 判断是否满意
	for(int i = 1; i <= 3; i++) { // 枚举每一行
		if(h[i][1] == max(h[i][1], max(h[i][2], h[i][3])))
			// 若最后打开 (i,1) 即先打开 (i,2) 和 (i,3)
			if(a[i][2] == a[i][3]) return 0;
		if(h[i][2] == max(h[i][1], max(h[i][2], h[i][3])))
			if(a[i][1] == a[i][3]) return 0;
		if(h[i][3] == max(h[i][1], max(h[i][2], h[i][3])))
			if(a[i][1] == a[i][2]) return 0;
	}
	for(int i = 1; i <= 3; i++) { // 枚举每一列
		if(h[1][i] == max(h[1][i], max(h[2][i], h[3][i])))
			if(a[2][i] == a[3][i]) return 0;
		if(h[2][i] == max(h[1][i], max(h[2][i], h[3][i])))
			if(a[1][i] == a[3][i]) return 0;
		if(h[3][i] == max(h[1][i], max(h[2][i], h[3][i])))
			if(a[1][i] == a[2][i]) return 0;
	}
	// 左上-右下对角线
	if(h[1][1] == max(h[1][1], max(h[2][2], h[3][3])))
		if(a[2][2] == a[3][3]) return 0;
	if(h[2][2] == max(h[1][1], max(h[2][2], h[3][3])))
		if(a[1][1] == a[3][3]) return 0;
	if(h[3][3] == max(h[1][1], max(h[2][2], h[3][3])))
		if(a[1][1] == a[2][2]) return 0;
  	// 右上-左下对角线
	if(h[1][3] == max(h[1][3], max(h[2][2], h[3][1])))
		if(a[2][2] == a[3][1]) return 0;
	if(h[2][2] == max(h[1][3], max(h[2][2], h[3][1])))
		if(a[1][3] == a[3][1]) return 0;
	if(h[3][1] == max(h[1][3], max(h[2][2], h[3][1])))
		if(a[1][3] == a[2][2]) return 0;
	return 1;
}
void work(int k) {
	if(k == 10) { // 所有格子的次序均已确定
		if(check()) cnt++; // 计数器累加
		return;
	}
	for(int i = 1; i <= 3; i++) 
		for(int j = 1; j <= 3; j++)
			if(!h[i][j]) { // 枚举还没有确定次序的格子赋值为 k
				h[i][j] = k;
				work(k + 1);
				h[i][j] = 0; // 注意要回溯
			}
}
int factorial(int i) { // 计算阶乘
	if(i == 1) return 1;
	return i * factorial(i - 1);
} 
int main() {
	for(int i = 1; i <= 3; i++)
		for(int j = 1; j <= 3; j++)
			cin>>a[i][j];
	work(1);
	double ans = cnt * 1.0 / factorial(9); // 注意要 * 1.0 强转 double 类型
	printf("%.9f", ans); // 保留 8 位小数输出
	return 0;
}

```

---

## 作者：robertuu (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc319_c)

没有什么很绝妙的技巧，直接暴力就行了。

由于只有 $9$ 个格子，全排列不会很多（离超时远着呢），可以先进行全排列，这样只需要验证每一种情况是否会不高兴就行了。

对于每种情况，依次扫描生成的序列，如果扫到一个数时其同行、同列、同对角线（有些格子就没有）上的其他格子是否都已经扫描并全部相等，如果有一种情况成立就说明会不高兴，将不高兴的次数加一。

答案：显然，答案是 $1 - \frac{cnt1}{cnt2}$，$cnt1$ 为总情况数，$cnt2$ 为不高兴的情况数

复杂度：$O(n! \times n)$，$n!$ 为全排列复杂度，$n$ 为检查复杂度。

代码（稍微有亿点长）：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[10],d[10];
bool flag[10];
int main()
{
	for(int i = 1;i <= 9;i++)
	{
		d[i] = i;
		cin >> a[i];
	}
	long long cnt1 = 0,cnt2 = 0;
	do
	{
		cnt1++;
		memset(flag,0,sizeof(flag)); // 记录是否已经看过
		for(int i = 1;i <= 9;i++) // 暴力检查
		{
			flag[d[i]] = 1;
			if(d[i] == 1)
			{
				if(flag[2] && flag[3] && a[2] == a[3])
				{
					cnt2++;
					break;
				}
				if(flag[4] && flag[7] && a[4] == a[7])
				{
					cnt2++;
					break;
				}
				if(flag[5] && flag[9] && a[5] == a[9])
				{
					cnt2++;
					break;
				}
			}
			if(d[i] == 2)
			{
				if(flag[1] && flag[3] && a[1] == a[3])
				{
					cnt2++;
					break;
				}
				if(flag[5] && flag[8] && a[5] == a[8])
				{
					cnt2++;
					break;
				}
			}
			if(d[i] == 3)
			{
				if(flag[1] && flag[2] && a[2] == a[1])
				{
					cnt2++;
					break;
				}
				if(flag[6] && flag[9] && a[6] == a[9])
				{
					cnt2++;
					break;
				}
				if(flag[5] && flag[7] && a[5] == a[7])
				{
					cnt2++;
					break;
				}
			}
			if(d[i] == 4)
			{
				if(flag[1] && flag[7] && a[1] == a[7])
				{
					cnt2++;
					break;
				}
				if(flag[5] && flag[6] && a[5] == a[6])
				{
					cnt2++;
					break;
				}
			}
			if(d[i] == 5)
			{
				if(flag[4] && flag[6] && a[4] == a[6])
				{
					cnt2++;
					break;
				}
				if(flag[2] && flag[8] && a[2] == a[8])
				{
					cnt2++;
					break;
				}
				if(flag[1] && flag[9] && a[1] == a[9])
				{
					cnt2++;
					break;
				}
				if(flag[3] && flag[7] && a[3] == a[7])
				{
					cnt2++;
					break;
				}
			}
			if(d[i] == 6)
			{
				if(flag[4] && flag[5] && a[4] == a[5])
				{
					cnt2++;
					break;
				}
				if(flag[3] && flag[9] && a[3] == a[9])
				{
					cnt2++;
					break;
				}
			}
			if(d[i] == 7)
			{
				if(flag[8] && flag[9] && a[8] == a[9])
				{
					cnt2++;
					break;
				}
				if(flag[4] && flag[1] && a[4] == a[1])
				{
					cnt2++;
					break;
				}
				if(flag[3] && flag[5] && a[5] == a[3])
				{
					cnt2++;
					break;
				}
			}
			if(d[i] == 8)
			{
				if(flag[2] && flag[5] && a[2] == a[5])
				{
					cnt2++;
					break;
				}
				if(flag[9] && flag[7] && a[9] == a[7])
				{
					cnt2++;
					break;
				}
			}
			if(d[i] == 9)
			{
				if(flag[7] && flag[8] && a[7] == a[8])
				{
					cnt2++;
					break;
				}
				if(flag[6] && flag[3] && a[3] == a[6])
				{
					cnt2++;
					break;
				}
				if(flag[1] && flag[5] && a[5] == a[1])
				{
					cnt2++;
					break;
				}
			}
		}
	}while(next_permutation(d+1,d+10)); // 全排列
	printf("%.10f",1.0-1.0*cnt2/cnt1);
	return 0;
}
```


---

## 作者：TG_Space_Station (赞：0)

# 思路
$3 \times 3$ 的方格，$9! = 362,880$，够挥霍的了。  
一道毫无思维难度的爆搜题，注意一下细节就好了。  
DFS 中：$cur$ 表示正在填第多少方格，$flag$ 表示目前是否已经失望。  
要更新 $flag$ 其实很简单，只需枚举出每种可能的失望方式，判断是否失望即可。  
总可能方案数：$ansd = 9!$。  
不失望方案数记为 $ansu$，通过搜索算出。  
最后答案即为 $\frac{ansu}{ansd} $。
# [AC Code](https://atcoder.jp/contests/abc319/submissions/45389595)
```
#include <bits/stdc++.h>
using namespace std;

long long a[5][5];
long long bj[5][5];
long long ansu, ansd;

void update(long long &flag)//更新falg，注意细节！！！
{
	int i;

	for(i = 1; i <= 3; i++)
	{
		if(bj[i][1] + bj[i][2] + bj[i][3] != 2)
			continue;
		if(bj[i][1] == 1 && bj[i][2] == 1 && a[i][1] == a[i][2])
			flag = 1;
		if(bj[i][1] == 1 && bj[i][3] == 1 && a[i][1] == a[i][3])
			flag = 1;
		if(bj[i][2] == 1 && bj[i][3] == 1 && a[i][2] == a[i][3])
			flag = 1;
	}
	for(i = 1; i <= 3; i++)
	{
		if(bj[1][i] + bj[2][i] + bj[3][i] != 2)
			continue;
		if(bj[1][i] == 1 && bj[2][i] == 1 && a[1][i] == a[2][i])
			flag = 1;
		if(bj[1][i] == 1 && bj[3][i] == 1 && a[1][i] == a[3][i])
			flag = 1;
		if(bj[2][i] == 1 && bj[3][i] == 1 && a[2][i] == a[3][i])
			flag = 1;
	}
	
	if(bj[1][1] + bj[2][2] + bj[3][3] == 2)
	{
		if(bj[1][1] == 1 && bj[2][2] == 1 && a[1][1] == a[2][2])
			flag = 1;
		if(bj[1][1] == 1 && bj[3][3] == 1 && a[1][1] == a[3][3])
			flag = 1;
		if(bj[3][3] == 1 && bj[2][2] == 1 && a[3][3] == a[2][2])
			flag = 1;
	}
	if(bj[1][3] + bj[2][2] + bj[3][1] == 2)
	{
		if(bj[1][3] == 1 && bj[2][2] == 1 && a[1][3] == a[2][2])
			flag = 1;
		if(bj[1][3] == 1 && bj[3][1] == 1 && a[1][3] == a[3][1])
			flag = 1;
		if(bj[3][1] == 1 && bj[2][2] == 1 && a[3][1] == a[2][2])
			flag = 1;
	}
}

void dfs(long long cur, long long flag)//cur表示正在填第多少方格，flag表示是否失望
{
	long long i, j;
	update(flag);
	
	if(cur == 10)
	{
		if(!flag)
			ansu++;//满足条件情况
		return;
	}
	
	for(i = 1; i <= 3; i++)
	{
		for(j = 1; j <= 3; j++)
		{
			if(bj[i][j])
				continue;
			
			bj[i][j] = 1;
			dfs(cur + 1, flag);
			bj[i][j] = 0;
		}
	}
}

int main()
{
	long long i, j;
	ansd = 1;

	for(i = 1; i <= 9; i++)
		ansd *= i;//一共可能情况
	
	for(i = 1; i <= 3; i++)
		for(j = 1; j <= 3; j++)
			cin >> a[i][j];
	
	dfs(1, 0);
	printf("%.8Lf", ansu * (long double)(1.0) / ansd); 
	return 0;
}
```

---

## 作者：Fire_flame (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc319_c)

## $\mathtt{Solution}$

一道简单的题目，但是实现有点复杂。

考虑把二维的数组压成一维，编号为 $1\sim9$。

那么直接枚举全排列，也就是它们的选取顺序。

最后再判断一下，如果高桥会沮丧，那么计数器 $num+1$，最终答案是 $1-\dfrac{num}{9!}$。

判断的时候，我为了偷懒写了双关键字排序，第一关键字是选取时间，第二关键字是方格的值。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){
	int s = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){s = s * 10 + (ch - '0');ch = getchar();}
	return s * f;
}
const int MAXN = 5;
int n, ans, a[MAXN][MAXN], used[MAXN * MAXN], b[MAXN * MAXN], c[MAXN][MAXN];
struct node{
	int x, y;
	bool operator < (const node &lyn)const{
		if(x != lyn.x)return x < lyn.x;
		return y < lyn.y;
	}
};
void calc(){
	int cnt = 0;
	for(int i = 1;i <= n;i ++){
		for(int j = 1;j <= n;j ++)c[i][j] = b[++ cnt];//把选取顺序从一维变成二维
	}
	for(int i = 1;i <= n;i ++){
		node p[4];
		p[1] = {c[i][1], a[i][1]};//判断行
		p[2] = {c[i][2], a[i][2]};
		p[3] = {c[i][3], a[i][3]};
		sort(p + 1, p + n + 1);
		if(p[1].y == p[2].y){
			ans ++;
			return ;
		}
	}
	for(int i = 1;i <= n;i ++){//判断列
		node p[4];
		p[1] = {c[1][i], a[1][i]};
		p[2] = {c[2][i], a[2][i]};
		p[3] = {c[3][i], a[3][i]};
		sort(p + 1, p + n + 1);
		if(p[1].y == p[2].y){
			ans ++;
			return ;
		}
	}
	node p[4];
	p[1] = {c[1][1], a[1][1]};//判断斜对角
	p[2] = {c[2][2], a[2][2]};
	p[3] = {c[3][3], a[3][3]};
	sort(p + 1, p + n + 1);
	if(p[1].y == p[2].y){
		ans ++;
		return ;
	}
	p[1] = {c[3][1], a[3][1]};//判断斜对角
	p[2] = {c[2][2], a[2][2]};
	p[3] = {c[1][3], a[1][3]};
	sort(p + 1, p + n + 1);
	if(p[1].y == p[2].y){
		ans ++;
		return ;
	}
}
void dfs(int x){
	if(x > n * n){
		calc();
		return ;
	}
	for(int i = 1;i <= n * n;i ++){//正常的全排列选取
		if(used[i])continue;
		b[x] = i, used[i] = 1;
		dfs(x + 1);
		used[i] = 0;
	}
}
int main(){
	n = 3;
	for(int i = 1;i <= n;i ++){
		for(int j = 1;j <= n;j ++)a[i][j] = read();
	}
	dfs(1);
	printf("%.12lf", 1 - 1.0 * ans / 362880);//362880即为9!
	return 0;
}

```


---

## 作者：liujy_ (赞：0)

### 题目大意
 一个 $9 \times 9$ 的网格，每个格子里面有一个数字，每次随机可以随机点开一个格子看到里面的数，如果每行或者每列或者每条对角线上先点开的两个数相同且最后一个数和前两个不相同，那么这个点开网格的顺序会让人失望，问不失望的概率是多少。   
 

------------

首先不能直接将每行每列和每条对角线的概率直接乘起来，因为它们之间是会互相影响的。答案可以转化不令人失望的点开序列方案数除以总方案数。   
考虑到一共只有 $9$ 个数，我们可以直接枚举所有的点开网格的方式，暴力的去判断是否合法。    

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<string>
#include<vector>
using namespace std;
const int N=2e5+5;
int n,a[20],cnt,ans;
int p[20];bool vis[20];
vector<int> g[N],v[N];
bool check(){bool flag=0;
	for(int i=0;i<=n;i++)v[i].clear();
	for(int i=1;i<=n;i++){
		for(auto x:g[p[i]]){
			v[x].push_back(a[p[i]]);
			if(v[x].size()==3)flag|=(v[x][0]==v[x][1]&&v[x][0]!=a[p[i]]);
		} 
	}
	return flag;
}
void dfs(int x){
	if(x>n){
		cnt++,ans+=check();
		return ;
	}
	for(int i=1;i<=n;i++)
		if(!vis[i]){
			p[x]=i;vis[i]=1;
			dfs(x+1);
			vis[i]=0;
		}
}
int main(){n=9;
	for(int i=1;i<=9;i++)scanf("%d",&a[i]),g[i].push_back((i+2)/3),g[i].push_back((i-1)%3+1+3);
	g[1].push_back(7);
	g[5].push_back(7);
	g[9].push_back(7);
	g[3].push_back(8);
	g[5].push_back(8);
	g[7].push_back(8);
	dfs(1);//cout<<cnt<<" "<<ans<<endl;
	printf("%.9lf",(double)(cnt-ans+0.0)/(cnt+0.0));
	return 0;
}

```


---

## 作者：KeatonBinary (赞：0)

# Solution？
提供一种暴力枚举的方案。按照从上到下、从左到右的顺序给每个数编号为 $[0,9)$，枚举选出的数的顺序的全排列，模拟检查是否满足不满意的条件并记录不满意的情况总数为 $cnt$，答案即为 $(ans-cnt)\div ans$。
# Code！
```cpp
#include <bits/stdc++.h>

using namespace std;

int c[5][5], row[5][10], col[5][10], x[2][10], cr[5], cc[5], cx[2], cnt, p[10];
double ans = 362880;

int main() {
  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 3; ++j) cin >> c[i][j];
  for (int i = 0; i < 9; ++i) p[i] = i;
  int fl;
  do {
    fl = 1, memset(row, 0, sizeof row), memset(col, 0, sizeof col),
    memset(x, 0, sizeof x), memset(cr, 0, sizeof cr), memset(cc, 0, sizeof cc),
    memset(cx, 0, sizeof cx);
    for (int id = 0, i, ro, co, n; fl && id < 9; ++id) {
      i = p[id], ro = i / 3, co = i % 3, n = c[ro][co];
      ++row[ro][n], ++col[co][n], ++cr[ro], ++cc[co];
      if (row[ro][n] == 2 && cr[ro] == 2 || col[co][n] == 2 && cc[co] == 2) {
        ++cnt;
        break;
      }
      if (ro == co) {
        ++x[0][n], ++cx[0];
        if (x[0][n] == 2 && cx[0] == 2) ++cnt, fl = 0;
      }
      if (fl && ro == 2 - co) {
        ++x[1][n], ++cx[1];
        if (x[1][n] == 2 && cx[1] == 2) ++cnt, fl = 0;
      }
    }

  } while (next_permutation(p, p + 9));
  printf("%.10f\n", (ans - cnt) / ans);
  return 0;
}
```

---

