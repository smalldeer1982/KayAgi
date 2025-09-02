# Posterized

## 题目描述

Professor Ibrahim has prepared the final homework for his algorithm’s class. He asked his students to implement the Posterization Image Filter.

Their algorithm will be tested on an array of integers, where the $ i $ -th integer represents the color of the $ i $ -th pixel in the image. The image is in black and white, therefore the color of each pixel will be an integer between 0 and 255 (inclusive).

To implement the filter, students are required to divide the black and white color range \[0, 255\] into groups of consecutive colors, and select one color in each group to be the group’s key. In order to preserve image details, the size of a group must not be greater than $ k $ , and each color should belong to exactly one group.

Finally, the students will replace the color of each pixel in the array with that color’s assigned group key.

To better understand the effect, here is an image of a basking turtle where the Posterization Filter was applied with increasing $ k $ to the right.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF980C/a5e04b9b80b48f601f9e0b203cd8ee3718afd0e4.png)To make the process of checking the final answer easier, Professor Ibrahim wants students to divide the groups and assign the keys in a way that produces the lexicographically smallest possible array.

## 说明/提示

One possible way to group colors and assign keys for the first sample:

Color $ 2 $ belongs to the group $ [0,2] $ , with group key $ 0 $ .

Color $ 14 $ belongs to the group $ [12,14] $ , with group key $ 12 $ .

Colors $ 3 $ and $ 4 $ belong to group $ [3, 5] $ , with group key $ 3 $ .

Other groups won't affect the result so they are not listed here.

## 样例 #1

### 输入

```
4 3
2 14 3 4
```

### 输出

```
0 12 3 3
```

## 样例 #2

### 输入

```
5 2
0 2 1 255 254
```

### 输出

```
0 1 1 254 254
```

# 题解

## 作者：Aragron_II (赞：4)

####  [CF980C Posterized题解](https://www.luogu.com.cn/problem/CF980C)





------------

#### 题意：
一种处理照片的手段，把相近的颜色统一替换成同一种颜色



#### 思路：
给一个大小为 $ n $ 的数组，将数组分组，一个组必须是连续的数字，且相差不超过 $ k $。要求字典序最小。所以可以肯定的是一组数字会被替换成这组数字的第一个，也就是最小的那个。

贪心处理，从当前数字 $ a[i] $ 往前，如果前面的数字 $ a[j] $ 还未分组，则分到一组。如果 $ a[j] $ 已分组，则判断 $ a[i] $ 能否合并到一组。

#### 代码：


```
#include <bits/stdc++.h>
using namespace std;
int n,k,p[100005],a[300];
int main() {
	memset(a,-1,sizeof(a)); //初始化 
	cin>>n>>k;
	for(int i=0;i<n;i++)
		cin>>p[i]; 
	//输入 
	for(int i=0;i<n;i++) {
		if(a[p[i]]==-1) {
			int t=max(0,p[i]-k+1);//不可为负
			for(int j=t;j<=p[i];j++) { //可能作为a数组的值
				if((a[j]==-1)||(p[i]-a[j])<k) {//j所在的组可以放进p[i]
					for(int k=j;k<=p[i];k++)
						a[k]=j; //赋值 
					break; //复制结束直接退出循环 
				}
			}
		}
	}
	for(int i=0;i<n;i++) //输出数字典序最小的情况 
		cout<<a[p[i]]<<' ';
	return 0;
}
```


---

## 作者：きりと (赞：3)

### 题目大意
 
这题的题面有点绕，大致是说：有 $n$ 个数，$p[1],p[2],...,p[n]$，都在    $[0,255]$ 之间。

现在我们可以将 $[0,255]$ 中的数分组，将每组里的所有数变成组内的某一个数，每组不得超过 $k$ 个数

求原数组 $p$ 经变换后能够使字典序最小的方案

### 解题思路

一眼看过去贪心，我们要保证操作后的数组的字典序最小，就要让出现在前面的数尽可能小，那么我们先 $O(n)$ 扫入 $p$ ，读到一个 $p$ 就向前找 $k$ 位，如果前面 $k$ 位都没被分过组那就以 $p[i]-k+1$ 位开头, $p[i]$ 结尾分一组，如果前面某一位开始分过了，那就从第一个没分过的开始分组，然后把组内元素全部更新为这个组的开头元素

实现用 $map+$ 暴力就彳亍

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10,M=257;
int p[N];
map<int,int>mp;
bool f[N];
signed main()
{
	int n,k;
	cin>>n>>k;
	for(int i=0;i<n;i++)
	{
		cin>>p[i];
	}
	for(int i=0;i<n;i++)
	{
		if(!f[p[i]])
		{
			for(int j=max(0,p[i]-k+1);j<=p[i];j++)
			{
				if(!f[j]||(p[i]-mp[j])<k)
				{
					for(int k=j;k<=p[i];k++)
					{
						f[k]=1;
						mp[k]=j;
					}
					break;
				}
			}
		}
	}
	for(int i=0;i<n;i++)
	{
		cout<<mp[p[i]]<<" ";
	}
	return 0;
}
```



---

## 作者：流绪 (赞：0)

求字典序最小的情况,那么我们从前往后枚举,贪心的让每一个数都取到它能取的区间的最小数,这样字典序就能最小了,一些细节的处理注释在代码里了

下面是 AC 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define inf 0x7f7f7f7f
using namespace std;
int a[1000010],b[266];
int main()
{
	ios::sync_with_stdio(false);
	int n,k;
	cin >> n >> k;
	memset(b,-1,sizeof(b));
	for(int i=1;i<=n;i++)
	{
		cin >> a[i];
		if(b[a[i]] == -1)//若这个数的区间还没取过 
		{
			int x;
			if(a[i] <= k-1)
				x=0;
			else
				x=a[i]-k+1;//贪心地取能取到的最小数 
			while(b[x]!=-1&&a[i]>b[x]+k-1)
				x++;//最小数被取过且这个区间不包括 a[i],增大,令其未被用过或能包含 a[i] 
			if(b[x] != -1)
				x = b[x]; //被用过,但能包含a[i]的情况 
			for(int j=a[i];~j&&j>=x;j--)
				b[j] = x;//覆盖,表示区间已经被找过 
		}
	}
	cout << b[a[1]] << " ";
	for(int i=2;i<=n;i++)
		cout << b[a[i]] << " ";
} 
```


---

## 作者：The_jester_from_Lst (赞：0)

考虑贪心。

题意有些曲折。实际上就是每个 $a_i$ 都能转化成 $a_i-k+1$ ~ $a_i+k-1$，然后同在这个范围里的数可以一起转化。

显然为了使字典序最小，把它变得更大是没有意义的。所以对于每一个 $a_i$，我们将它变化后的结果存在 $vis_{a_i}$ 中，因为在同一个范围里的数可以变为同一个数，所以每次循环从小到大遍历这个 $a_i$ 可以变化的范围，把这个范围里未修改过的数全部一起转化为当前的这个值，就一定是最小的值。

最后对于每一个 $a_i$，输出对应的 $vis_{a_i}$ 即可。

附上代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define il inline
#define pii pair<int,int>
#define mk make_pair
using namespace std;
il int rd(){
    int jya=0,tl=1;char jyt=getchar();
    while(!isdigit(jyt)){if(jyt=='-')tl=-1;jyt=getchar();}
    while(isdigit(jyt)){jya=jya*10+(jyt-'0');jyt=getchar();}
    return jya*tl;
}
il void wr(int jjy){
    if(jjy<0)putchar('-'),jjy=-jjy;
    if(jjy>9)wr(jjy/10);
    putchar(jjy%10+48);
}
il int max(int x,int y){return x>=y?x:y;}
il int min(int x,int y){return x<=y?x:y;}
const int JYAAKIOI=1145141919810;
int n,k,a[100086],vis[100086];
signed main(){
	n=rd();k=rd();
	memset(vis,-1,sizeof vis);
	for(int i=1;i<=n;++i)a[i]=rd();
	for(int i=1;i<=n;++i){
		if(vis[a[i]]!=-1)continue;
		for(int j=max(a[i]-k+1,0);j<=a[i];++j){
			if(vis[j]==-1||abs(vis[j]-a[i])<k){
				for(int c=j;c<=a[i];++c)vis[c]=j;
				break;
			}
		}
	}
	for(int i=1;i<=n;++i)wr(vis[a[i]]),putchar(' ');
	return 0;
}
```

---

