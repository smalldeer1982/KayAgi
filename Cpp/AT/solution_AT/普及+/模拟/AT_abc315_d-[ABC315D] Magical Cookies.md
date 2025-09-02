# [ABC315D] Magical Cookies

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc315/tasks/abc315_d

$ H\ \times\ W $ 枚のクッキーが $ H $ 行 $ W $ 列に並んでいます。  
上から $ i $ 行目・左から $ j $ 列目のクッキーの色は英小文字 $ c_{i,j} $ で表されます。

これから、以下の手続きを行います。

1\. 各行に対して次の操作を行う : その行に $ 2 $ 枚以上のクッキーが残っており、それらの色がすべて同じならば、それらに印をつける。

2\. 各列に対して次の操作を行う : その列に $ 2 $ 枚以上のクッキーが残っており、それらの色がすべて同じならば、それらに印をつける。

3\. 印のついたクッキーがあればそれらをすべて取り除いて 1. に戻り、なければ手続きを終了する。

手続きを終了した時点で残っているクッキーの枚数を求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ H,\ W\ \leq\ 2000 $
- $ c_{i,j} $ は英小文字である

### Sample Explanation 1

以下で示す順で手続きを行います。 - 1. により、$ 1,\ 2 $ 行目のクッキーに印をつける。 - 2. により、$ 1 $ 列目のクッキーに印をつける。 - 3. により、印を付けたクッキーを取り除く。 この時点でクッキーは以下のようになっています。ただし、クッキーを取り除いた箇所は `.` で表しています。 ``` ... ... .bc .bd ``` - 1. により、何もしない。 - 2. により、$ 2 $ 列目のクッキーに印をつける。 - 3. により、印を付けたクッキーを取り除く。 この時点でクッキーは以下のようになっています。ただし、クッキーを取り除いた箇所は `.` で表しています。 ``` ... ... ..c ..d ``` - 1. により、何もしない。 - 2. により、何もしない。 - 3. により、印がついているクッキーが存在しないので手続きを終了する。 最終的に残っているクッキーの枚数は $ 2 $ 枚です。

## 样例 #1

### 输入

```
4 3
aaa
aaa
abc
abd```

### 输出

```
2```

## 样例 #2

### 输入

```
2 5
aaaaa
abcde```

### 输出

```
4```

## 样例 #3

### 输入

```
3 3
ooo
ooo
ooo```

### 输出

```
0```

# 题解

## 作者：_zzzzzzy_ (赞：5)

# 思路

发现我们可以用暴力过掉这个题。

我们记两个数组 $st1_{i,ch},st2_{j,ch}$ 表示行和列出现了几次 $ch$。

然后我们循环一次然后对于每一行每一列都循环一遍判断是否能删除，然后把能删除的行和列记录在数组里，然后删除行和列。

发现每次必定是要删掉一行或一列的，那么复杂度就是 $O((n+m)^2)$ 的了。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2050;
int n, m, st1[maxn][26], st2[maxn][26];
char mp[maxn][maxn];
bool vis1[maxn], vis2[maxn];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> mp[i][j];
		}
		for (int j = 1; j <= m; j++) {
			st1[i][mp[i][j] - 'a']++;
			st2[j][mp[i][j] - 'a']++;
		}
	}
	while(1) {
		vector<int> r, c;
		for (int i = 1; i <= n; i++) {
			if (!vis1[i]) {
				int cnt = 0, tot = 0;
				for (int j = 0; j <26;j++) {
					cnt += st1[i][j] > 0;
					tot += st1[i][j];
				}
				if (cnt == 1 && tot > 1) {
					r.push_back(i);
				}
			}
		}
		for (int i = 1; i <= m; i++) {
			if (!vis2[i]) {
				int cnt = 0, tot = 0;
				for (int j = 0; j < 26; j++) {
					cnt += st2[i][j] > 0;
					tot += st2[i][j];
				}
				if (cnt == 1 && tot > 1) {
					c.push_back(i);
				}
			}
		}
		for (int x : r) {
			vis1[x] = 1;
			for (int j = 1; j <= m; j++) {
				if (mp[x][j] != '.') {
					st1[x][mp[x][j] - 'a']--;
					st2[j][mp[x][j] - 'a']--;
				}
				mp[x][j] = '.';
			}
		}
		for (int x : c) {
			vis2[x] = 1;
			for (int j = 1; j <= n; j++) {
				if (mp[j][x] != '.') {
					st1[j][mp[j][x] - 'a']--;
					st2[x][mp[j][x] - 'a']--;
				}
				mp[j][x] = '.';
			}
		}
		if (!r.size() && !c.size()) {
			break;
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			ans += (mp[i][j] != '.');
		}
	}
	cout << ans << "\n";
	return 0;
}
```

---

## 作者：banned_xiejiayun (赞：4)

~~xxs又来写题解了~~

[题目](https://www.luogu.com.cn/problem/AT_abc315_d)



### 题目大意

给出 $H \times W$ 的地图，不断进行以下操作：

1. 选定某行，若这行字母数 $\ge 2$，并且全是相同的，将其标记。

1. 选定某列，若这列字母数 $\ge 2$，并且全是相同的，将其标记。

1. 把目前标记删除，若无删除，结束操作，否则重新跳回操作 1。

$1 \le H,W \le 2000$。

### 思路分析

老实说，这道题除了模拟真的没有别的方法。

每次一行一行地判断，一个一个地去删除，时间复杂度可能会达到 $O(n^3)$，算一下 $2000^3=8\times10^9$。这个做法当然会非常完美地 TLE。

所以只能优化。

在题目下边有一句尤其重要的话：

- $ c_{i,j} $ は英小文字である

翻译成中文：$ c_{i,j} $ 是小写字母。

也就是说，对于每一行（每一列），只可能有 $26$ 种情况：全是 $a$，全是 $b$，全是 $c$，全是 $d$，全是 $e$……

我们建一个桶来记录这一行（这一列）分别有几个 $a$，几个 $b$，几个 $c$……

于是这一重循环就降到了常数级，整体时间复杂度就是 $O(n^2)$，再加上 $2$ 秒的时限就可以 AC 了。


------------

当然实现起来可能还有些问题需要处理，详细的见代码吧。

## AC code：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, m;
int x, y;
bool h_flag[2010], l_flag[2010];//标记每一行是否删除
int h_c[2010][30], l_c[2010][30];//每一行（列）的字母统计
int h_c_tmp[2010][30], l_c_tmp[2010][30];//每一行（列）每个字母删除的个数
char c;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> c;
			h_c[i][c - 'a']++;
			l_c[j][c - 'a']++;//初始统计
		}
	}
	int nn = n, mm = m, ans = n * m;
	//nn mm 是现在矩阵的长和宽
	//ans 默认是一个也没删除
	while (1) {
//		cout << nn << ' ' << mm << ' ' << ans << '\n';
		if (nn < 2 && mm < 2)break;//这种情况下已经不可能再删了
		x = 0;
		y = 0;
		memset(h_c_tmp, 0, sizeof(h_c_tmp));
		memset(l_c_tmp, 0, sizeof(l_c_tmp));
		bool flag_n = 0, flag_m = 0;//标记是否有删除一个行
		int nn__ = nn; //临时的nn__
		if (mm >= 2) {
			//行内元素>=2
			for (int i = 1; i <= n; i++) {
				if (h_flag[i])continue;//如果已经被删过了，就跳过
				for (int j = 0; j < 26; j++) {
					if (h_c[i][j]) {
						if (h_c[i][j] == mm) {//如果这个字母占了整一行
							if (!flag_n)flag_n = 1;
							ans -= mm;
							x++;//删除的行++
							h_flag[i] = 1;//标记为已删
							nn__--;//长度--
							for (int k = 1; k <= m; k++) {
								l_c_tmp[k][j]++;//记录这一行
							}
						} else break;
						//如果这个字母有，但是不是全部，就代表这一行不可能全相等
					}
				}
			}
		}
		
		//删列和删行一个道理：
		int mm__ = mm;
		if (nn >= 2) {
			for (int i = 1; i <= m; i++) {
				if (l_flag[i])continue;
				for (int j = 0; j < 26; j++) {
					if (l_c[i][j]) {
						if (l_c[i][j] == nn) {
							if (!flag_m)flag_m = 1;
							ans -= nn;
							y++;
							l_flag[i] = 1;
							mm__--;
							for (int k = 1; k <= n; k++) {
								h_c_tmp[k][j]++;
							}
						} else break;
					}
				}
			}
		}
		if (!flag_m && !flag_n)break;//如果两个都没删成，就没得删除
		for (int i = 1; i <= m; i++)
			for (int j = 0; j < 26; j++) {
				l_c[i][j] -= l_c_tmp[i][j];
			}
		for (int i = 1; i <= n; i++)
			for (int j = 0; j < 26; j++) {
				h_c[i][j] -= h_c_tmp[i][j];
			}
		ans += x * y;//删除了x行y列，中间会重复删x*y个，加回来。
		nn = nn__;
		mm = mm__;
	}
	cout << ans;
	return 0;
}
```

### 补充：

有人可能不理解为啥我还要专门建一个 l_c_tmp 和 h_c_tmp 来统计每个字母删除的个数。

假设一下，如果你在循环的过程中就把它删了，就可能导致误判“字母完全相同”。

比如：
```
aaa
aaa
bbc
```
理论上来讲，应该是先上了前两行 $a$ 然后就退出；
但是如果在循环删除行的时候就将 $a$ 的个数减掉，循环列的时候就会把 $b$ 也删除，答案就错了。

~~写的还不错吧……~~

---

## 作者：FBW2010 (赞：2)

# 思路
很明显，这是一道模拟题，如果用纯暴力方法做，就得先花 $O(n)$ 的时间重复执行每一个步骤，再用 $O(n^2)$ 的时间判断和删除，总共 $O(n^3)$，显然 TLE。

那怎么优化呢？我们会发现每删一条边后很有可能会有另一条边被解放，所以最开始的 $O(n)$ 是优化不了的，因此只能从每次的判断入手。于是，我们可以想到用两个桶来保存每行和每列的字母数量，就能优化到 $O(26n^2)$ 了。具体细节看代码。
# 代码
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
const int M=2005;
int h,w,ans; //表示长、宽和答案 
int a[M][M]; //二位数组 
int b1[M][26],b2[M][26]; //桶，表示每行或每列每种字母出现次数 
int f1[M],f2[M]; //标记那些行列被删除 
int main(){
	scanf("%d %d\n",&h,&w);
	ans=h*w; //刚开始有h*w个 
	
	//输入 
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			scanf("%c",&a[i][j]);
			//初始化桶 
			b1[i][a[i][j]-'a']++;
			b2[j][a[i][j]-'a']++;
		}
		scanf("\n");
	}
	
	//开始循环 
	while(1){
		int f=1; //标记有没有可以删除的 
		for(int i=1;i<=h;i++){
			if(f1[i]==2)continue; //如果这一列被删除就跳过 
			int cnt=0; //记录有几种字母 
			for(int j=0;j<26;j++){
				if(b1[i][j]){ //如果有这种字母 
					cnt++; //数量增加 
					if(cnt>1||b1[i][j]<2){ //如果超过一种或少于两个 
						cnt=2; //将少于两个的标记 
						break; 
					}
				}
			}
			if(cnt==1){ //满足要求 
				f=0; //有可以删除的 
				f1[i]=1; //标记为将要删除 
			}
		}
		
		//同上 
		for(int i=1;i<=w;i++){
			if(f2[i]==2)continue;
			int cnt=0;
			for(int j=0;j<26;j++){
				if(b2[i][j]){
					cnt++;
					if(cnt>1||b2[i][j]<2){
						cnt=2;
						break;
					}
				}
			}
			if(cnt==1){
				f=0;
				f2[i]=1;
			}
		}
		
		if(f)break; //如果没有可以删除的就结束 
		
		//删边 
		for(int i=1;i<=h;i++){
			if(f1[i]==1){ //被标记过将要删除 
				f1[i]=2; //标记为已删除 
				//调整桶数量 
				for(int j=1;j<=w;j++){ 
					if(f2[j]!=2){ //这一列没有被删除 
						//将这个字母数量减少 
						b1[i][a[i][j]-'a']--;
						b2[j][a[i][j]-'a']--;
						ans--; //被删一个 
					}
				}
			}
		}
		
		//同上 
		for(int i=1;i<=w;i++){
			if(f2[i]==1){
				f2[i]=2;
				for(int j=1;j<=h;j++){
					if(f1[j]!=2){
						b1[j][a[j][i]-'a']--;
						b2[i][a[j][i]-'a']--;
						ans--;
					}
				}
			}
		}
	}
	printf("%d",ans); //输出 
	return 0; //华丽的结尾 
}
```

---

## 作者：xiaoming007 (赞：1)

首先存在一种十分暴力的思路是直接暴力判断每个行/列是否要被删除，此时复杂度 $O(n^3)$。

考虑优化，我们可以记录每条行/列出现的每个字符的数量，如果当前字符出现的数量等于当前行/列数，可以删除。

然后因为删掉了一个行/列，所以记录行列总数的要减一（不要减 $n$ 或 $m$，因为删的不一定是边角的）。

因为最多删 $n+m-2$ 次，每次 $O(n+m)$ 判，去掉常数所以复杂度是 $O(n^2)$ 的。

---

## 作者：Neil_Qian (赞：1)

# [ABC315D] Magical Cookies 题解

## 题目描述

给定一个由小写字母组成的 $n\times m$ 的矩阵，执行一下操作知道无法执行：对于每一行和每一列，如果字母都相同，则标记这些字母。将所有有标记的字母都删去。求最后有多少个字母。$n,m\le2000$。

## 解决方案

设 $n,m$ 同阶。一眼复杂度 $O(n^2)$ 或者 $O(26n^2)$，直接上模拟。

每一行和每一列记录它每个字母出现的次数，那么可以在 $O(26)$ 的时间内检查是否合法。如果合法，即这一行或这一列需要删除，则将它包含的所有列或所有行更新，时间复杂度 $O(n)$。注意根据题意，要行和列都检查完了才能更新。一共只有 $O(n)$ 个这样的行或列，所以非常极端的情况下时间复杂度 $O(26n^2)$，显然跑不满，实际测试比 $O(n^2)$ 还快一些。一些细节看代码。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;char c;bool flag;vector<int> v1,v2,a1,a2;
int n,m,a[2002][2002],s1[2002][27],s2[2002][27],ans,c1,c2,i,j,d,p,r1,r2;
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0),cin>>n>>m,ans=n*m;
	for(i=1;i<=n;i++)for(j=1;j<=m;j++)cin>>c,a[i][j]=c-'a';
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++)s1[i][a[i][j]]++;
		v1.push_back(i);
	}
	for(i=1;i<=m;i++){
		for(j=1;j<=n;j++)s2[i][a[j][i]]++;
		v2.push_back(i);
	}
	while(1){
		flag=0,a1.clear(),a2.clear(),r1=r2=0;
		if(c2<=m-2)for(d=0;d<v1.size();d++){
			i=v1[d],p=0;
			for(j=0;j<26;j++){
				p+=(s1[i][j]>0);
				if(p>=2)break;//超过一种，直接失败
			}
			if(p==1)a1.push_back(i),r1++,ans-=(m-c2-r2),//有一些已经删除了，不能重复统计
				v1.erase(v1.begin()+d),d--,flag=1;//把这一行删掉，不然会增加常数
		}
		if(c1<=n-2)for(d=0;d<v2.size();d++){//同上
			i=v2[d],p=0;
			for(j=0;j<26;j++){
				p+=(s2[i][j]>0);
				if(p>=2)break;
			}
			if(p==1)a2.push_back(i),r2++,ans-=(n-c1-r1),
				v2.erase(v2.begin()+d),d--,flag=1;
		}
		c1+=r1,c2+=r2;
		for(int i:a1)for(j=1;j<=m;j++)s2[j][a[i][j]]--;//更新字母数量
		for(int i:a2)for(j=1;j<=n;j++)s1[j][a[j][i]]--;
		if(!flag)break;//没有删除，直接退出
	}
	return cout<<ans<<"\n",0;
}
```


---

## 作者：Zi_Gao (赞：1)

## 前言

这个题是我第一次在比赛上切这么高评分的题，感觉不难但是似乎很多人现场没切出来。

## 正文

### 0x00 题目分析

下文默认行和列为 $n m$,并且同阶。

这道题简洁明了啊，假如直接按照题意模拟。分析时间复杂度，每次执行程序最多减少一行和一列，那么最劣需要循环 $\mathcal{O}\left(n\right)$ 次，进而考虑循环内部如何实现，检查每一行每一列是否符合条件需要 $\mathcal{O}\left(n^2\right)$；标记时间复杂度需要 $\mathcal{O}\left(n\right)$ 到 $\mathcal{O}\left(n^2\right)$，此时时间复杂度已经到了 $\mathcal{O}\left(n^3\right)$。显然过不了。

考虑进行优化，可以发现实际上标记的时间复杂度并不是$\mathcal{O}\left(n^3\right)$ 的，均摊下来只有 $\mathcal{O}\left(n^2\right)$。进而考虑优化寻找符合条件的行和列，这个过程实际上再说这个行/列的元素中种类是否只有一个元素，并且元素个数大于 $2$，动态维护带删除，实际上可以考虑把每一行和每一列开一个桶，记录这一行这一列出现的 $26$ 个字母有哪些即可，这样遍历行和列只需要 $\mathcal{O}\left(26\right)$ 即可。最终时间复杂度 $\mathcal{O}\left(n^2\right)$。

### 0x01 代码实现

行列分开讨论十分啰嗦，可以考虑和在一起，就是开桶的时候前面放行的桶，后面放列的桶即可，这样一个循环即可。

AC CODE

```cpp
#include<bits/stdc++.h>
// #define ONLINE_JUDGE
#define INPUT_DATA_TYPE int
#define OUTPUT_DATA_TYPE int
INPUT_DATA_TYPE read(){register INPUT_DATA_TYPE x=0;register char f=0,c=getchar();while(c<'0'||'9'<c)f=(c=='-'),c=getchar();while('0'<=c&&c<='9')x=(x<<3)+(x<<1)+(c&15),c=getchar();return f?-x:x;}void print(OUTPUT_DATA_TYPE x){register char s[20];register int i=0;if(x<0){x=-x;putchar('-');}if(x==0){putchar('0');return;}while(x){s[i++]=x%10;x/=10;}while(i){putchar(s[--i]+'0');}return;}

std::bitset<2010> mark[2010];
std::vector<int> mk;
int cnt[4010][26];
char map[2010][2010];

int main(){
	#ifndef ONLINE_JUDGE
	freopen("name.in", "r", stdin);
	freopen("name.out", "w", stdout);
	#endif

    register char c;
    register int i,j,flag=0,flag2=0,res=0;
    int n=read();
    int m=read();

    for(i=0;i<n;++i)
        for(j=0;j<m;++j){
            loop:c=getchar();
            if(c<'a'||'z'<c) goto loop;
            map[i][j]=c-'a';
            ++cnt[i][map[i][j]];//把行和列记录在一起
            ++cnt[n+j][map[i][j]];
        }

    while(1){
        mk.clear();
        for(i=0;i<n+m;++i){
            flag=flag2=0;//flag:有多少个种类 flag2:有多少个元素
            for(j=0;j<26;++j)
                flag+=(cnt[i][j]?1:0),flag2+=cnt[i][j];
            if(flag==1&&flag2>=2)
                mk.push_back(i);//将要标记的
        }
        if(mk.empty()) break;
        for(auto i:mk)
            if(i>=n){//列的情况
                i-=n;
                for(j=0;j<n;++j)
                    if(!mark[j][i]){
                        mark[j][i]=1;
                        res-=1;
                        --cnt[j][map[j][i]];
                        --cnt[n+i][map[j][i]];
                    }
            }else//行的情况
                for(j=0;j<m;++j)
                    if(!mark[i][j]){
                        mark[i][j]=1;
                        res-=1;
                        --cnt[i][map[i][j]];
                        --cnt[n+j][map[i][j]];
                    }
    }

    print(n*m+res);

	#ifndef ONLINE_JUDGE
	fclose(stdin);
	fclose(stdout);
	#endif
    return 0;
}
```

---

## 作者：cosf (赞：0)

## [ABC315D](https://atcoder.jp/contests/abc315/tasks/abc315_d) [魔法饼干](https://www.luogu.com.cn/problem/AT_abc315_d)

## 思路

有一种玄学做法，是这样的：

1. 将所有的能删的行删掉；
2. 将所有的能删的列删掉；
3. 回到步骤 1。

然后可以发现，样例 1 和样例 3 都过了。但是，样例 2 没过，我们看看它长什么样：

```input2
aaaaa
abcde
```

可以发现，如果能先把第 1 列删掉再删第 1 行，那么就可以得到正确答案 4 了。

也就是说，除了统计先删行再删列的结果，也要计算先删列再删行的结果（步骤 1 和步骤 2 调换）。

注意到，这样求出来的答案一定不会比标准答案小，因此可以放心取 $\min$。

---

至于具体怎么计算有哪一些行和列是可以删的，我们可以维护数组 $r[N], c[N]$ 以及 $row[N][27], col[N][27]$，分别表示这一行（列）的不同颜色的个数，这一行（列）的没删的个数（$row[N][0], col[N][0]$），以及每种颜色在这一行（列）的个数。

这样整个程序的复杂度就降到 $O((n+m)^2)$ 了。

---

最后说点更加玄学的东西。

在校内镜像域中，如果只计算先行后列可以得到 94 分的高分（满分 100），只计算先列后行可以得到 93 分的高分。综合一下却只能得到 100 分的低分了。

---

## [代码](https://www.luogu.com.cn/record/126142398)

```cpp
// 考场代码，不喜勿喷（bushi
#include <iostream>
#include <set>
using namespace std;

#define MAXN 2005 

int row[MAXN][27], col[MAXN][27];

int r[MAXN], c[MAXN];

set<int> ro, co;
set<int> rr, cc;

int mp[MAXN][MAXN];


int row2[MAXN][27], col2[MAXN][27];

int r2[MAXN], c2[MAXN];

set<int> ro2, co2;
set<int> rr2, cc2;

int mp2[MAXN][MAXN];

int main()
{
	int h, w;
	cin >> h >> w;
	for (int i = 1; i <= h; i++)
	{
		for (int j = 1; j <= w; j++)
		{
			char ch;
			cin >> ch;
			ch -= 'a';
			mp[i][j] = ch;
			mp2[i][j] = ch;
			if (!row[i][ch])
			{
				r[i]++;
				r2[i]++;
			}
			row[i][ch]++;
			row2[i][ch]++;
			if (!col[j][ch])
			{
				c[j]++;
				c2[j]++;
			}
			col[j][ch]++;
			col2[j][ch]++;
		}
		ro.insert(i);
		ro2.insert(i);
		row[i][26] = w;
		row2[i][26] = w;
	}
	for (int j = 1; j <= w; j++)
	{
		co.insert(j);
		co2.insert(j);
		col[j][26] = h;
		col2[j][26] = h;
	}
	// first
	int su = w * h;
	while (true)
	{
		int e = 0;
		
		
		cc.clear();
		for (int j : co)
		{
			if (c[j] == 1 && col[j][26] > 1)
			{
				e = 1;
				col[j][26] = 0;
				cc.insert(j);
				for (int i = 1; i <= h; i++)
				{
					if (mp[i][j] != 26)
					{
						su--;
						row[i][mp[i][j]]--;
						row[i][26]--;
						if (!row[i][mp[i][j]])
						{
							r[i]--;
						}
						mp[i][j] = 26;
					}
				}
			}
		}
		for (int j : cc)
		{
			co.erase(j);
		}
		rr.clear();
		for (int i : ro)
		{
			if (r[i] == 1 && row[i][26] > 1)
			{
				e = 1;
				row[i][26] = 0;
				rr.insert(i);
				for (int j = 1; j <= w; j++)
				{
					if (mp[i][j] != 26)
					{
						su--;
						col[j][mp[i][j]]--;
						col[j][26]--;
						if (!col[j][mp[i][j]])
						{
							c[j]--;
						}
						mp[i][j] = 26;
					}
				}
			}
		}
		for (int i : rr)
		{
			ro.erase(i);
		}
		if (!e)
		{
			break;
		}
	}
	// second
	int su2 = w * h;
	while (true)
	{
		int e = 0;
		rr2.clear();
		for (int i : ro2)
		{
			if (r2[i] == 1 && row2[i][26] > 1)
			{
				e = 1;
				row2[i][26] = 0;
				rr2.insert(i);
				for (int j = 1; j <= w; j++)
				{
					if (mp2[i][j] != 26)
					{
						su2--;
						col2[j][mp2[i][j]]--;
						col2[j][26]--;
						if (!col2[j][mp2[i][j]])
						{
							c2[j]--;
						}
						mp2[i][j] = 26;
					}
				}
			}
		}
		for (int i : rr)
		{
			ro.erase(i);
		}
		cc2.clear();
		for (int j : co2)
		{
			if (c2[j] == 1 && col2[j][26] > 1)
			{
				e = 1;
				col2[j][26] = 0;
				cc2.insert(j);
				for (int i = 1; i <= h; i++)
				{
					if (mp2[i][j] != 26)
					{
						su2--;
						row2[i][mp2[i][j]]--;
						row2[i][26]--;
						if (!row2[i][mp2[i][j]])
						{
							r2[i]--;
						}
						mp2[i][j] = 26;
					}
				}
			}
		}
		for (int j : cc2)
		{
			co2.erase(j);
		}
		if (!e)
		{
			break;
		}
	}

	cout << min(su, su2) << endl;
	return 0;
}
```


---

## 作者：Y2y7m (赞：0)

这是白给题，但是题面好容易让人误解（每次一行必须所有的相同才能删，而不是有两个字符相同就能删），导致好多人都卡住了。

就是每次暴力看看能不能删掉某行或某列，如果能，就暴力把这一整个行或列删掉，然后把这行或列标记上，如果不能删掉就直接结束，这样就能保证每次至少删掉一行或一列，时间复杂度就是对的。

代码：

```cpp
#include <bits/stdc++.h>

using namespace std;
const int maxn=2010;
int n,m;
char a[maxn][maxn];
int cntr[maxn][30],cntc[maxn][30];
int visr[maxn],visc[maxn];

int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i]+1;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++) cntc[i][a[i][j]-'a']++;
	}
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=n;j++) cntr[i][a[j][i]-'a']++;
	}
	int now=1e4;
	while(1)
	{
		now--;
		for(int i=1;i<=n;i++) visr[i]=visc[i]=0;
		for(int i=1;i<=n;i++)
		{
			if(visc[i]) continue;
			int flag=0,f=0;
			for(int j=0;j<26;j++)
			{
				if(cntc[i][j]) flag++;
				if(cntc[i][j]>=2) f=1;
			}
			if(flag!=1||!f) continue;
			visc[i]=now;
		}
		for(int i=1;i<=m;i++)
		{
			if(visr[i]) continue;
			int flag=0,f=0;
			for(int j=0;j<26;j++)
			{
				if(cntr[i][j]) flag++;
				if(cntr[i][j]>=2) f=1;
			}
			if(flag!=1||!f) continue;
			visr[i]=now;
		}
		bool flag=0;
		for(int i=1;i<=n;i++)
		{
			if(visc[i]!=now) continue;
			for(int j=0;j<26;j++) cntc[i][j]=0;
			flag=1;
			for(int j=1;j<=m;j++) if(a[i][j]!='.') cntr[j][a[i][j]-'a']--,a[i][j]='.';
		}
		for(int i=1;i<=m;i++)
		{
			if(visr[i]!=now) continue;
			for(int j=0;j<26;j++) cntr[i][j]=0;
			flag=1;
			for(int j=1;j<=n;j++) if(a[j][i]!='.') cntc[j][a[j][i]-'a']--,a[j][i]='.';
		}
		if(!flag) break;
	}
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++) if(a[i][j]!='.') ans++;
	}
	cout<<ans<<endl;
	return 0;
}

```


---

## 作者：robertuu (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc315_d)

### 方法 1：暴力法（AC 不了）

对于每一次删除，枚举每一行每一列，如果是完全相同且大于 $2$ 个就删除，把这一行或列标记为不存在，之后的枚举中跳过。

但是这种做法会被下面的这种类型的样例卡掉：
```
aaaaa
bcccc
bdeee
bdfgg
bdfhi
```
这时这个方法会运行 $2n$ 次，每一次的复杂度是 $O(n^2)$，总复杂度是 $O(n^3)$，会 `TLE`。

~~由于 AT 会记录罚时，我在赛时没有尝试这种方法~~

### 方法 2：优化版本

读入时统计每一行的每个字母出现了几次，出现过几个不同的字母，同时初始化还有几个字符没被删除，复杂度为 $O(n^2)$。

每一次操作时，对每一行每一列判断剩余字符是否大于等于 $2$ 个，种类数是否为 $1$，如果是，标记为在这一次扫描删除了它。

在扫描结束时，对每一个删除的行（列）进行处理（一定不能扫到一个处理一个，题目的逻辑是行列都标记完了再删除），找到那个唯一剩余的字符，把所有的列（行）的这个字符数量为减少 $1$，剩余可用字符数量减少 $1$， 如果这个字符的数量变成了 $0$，相当于这个字符消失了，把剩余字符类型数减 $1$。

这个优化版本每次操作的复杂度为 $O(xn)$（$x$ 为字母数量，英文小写仅为 $26$，远小于 $n$），总复杂度为 $O(xn^2)$，可以 AC

AC code：
``` cpp
#include<bits/stdc++.h>
using namespace std;
char s[2001][2001];
int n,m,line[2001][30],col[2001][30],l[2001],c[2001];
int tmpl[2001],tmpc[2001],suml[2001],sumc[2001],sz;
bool remove()
{
	sz++;
	// lines
	for(int i = 1;i <= n;i++)
		if(!tmpl[i] && suml[i] > 1 && l[i] == 1) tmpl[i] = sz;
	// cols
	for(int i = 1;i <= m;i++)
		if(!tmpc[i] && sumc[i] > 1 && c[i] == 1) tmpc[i] = sz;
	// remove
	int tar,flag = 0;
	for(int i = 1;i <= n;i++)
		if(tmpl[i] == sz)
		{
			flag = 1;
			for(int j = 1;j <= 26;j++)
				if(line[i][j])
				{
					tar = j;
					break;
				}
			for(int j = 1;j <= m;j++) // SLOW!!
			{
				col[j][tar]--; sumc[j]--;
				if(!col[j][tar]) c[j]--;
			}
		}
	for(int i = 1;i <= m;i++)
		if(tmpc[i] == sz)
		{
			flag = 1;
			for(int j = 1;j <= 26;j++)
				if(col[i][j])
				{
					tar = j;
					break;
				}
			for(int j = 1;j <= n;j++) // SLOW!!
			{
				line[j][tar]--; suml[j]--;
				if(!line[j][tar]) l[j]--;
			}
		}
	return flag;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++)
	{
		scanf("%s",s[i]+1);
		for(int j = 1;j <= m;j++)
		{
			line[i][s[i][j]-'a'+1]++;
			col[j][s[i][j]-'a'+1]++;
			if(line[i][s[i][j]-'a'+1] == 1) l[i]++; // new type
			if(col[j][s[i][j]-'a'+1] == 1) c[j]++; // new type
		}
	}
	for(int i = 1;i <= n;i++) suml[i] = m;
	for(int i = 1;i <= m;i++) sumc[i] = n;
	while(remove());
	int ans = 0;
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++)
			if(!tmpl[i] && !tmpc[j]) ans++;
	printf("%d",ans);
	return 0;
}
```



---

