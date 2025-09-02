# Exact Neighbours (Easy)

## 题目描述

The only difference between this and the hard version is that all $ a_{i} $ are even.

After some recent attacks on Hogwarts Castle by the Death Eaters, the Order of the Phoenix has decided to station $ n $ members in Hogsmead Village. The houses will be situated on a picturesque $ n\times n $ square field. Each wizard will have their own house, and every house will belong to some wizard. Each house will take up the space of one square.

However, as you might know wizards are very superstitious. During the weekends, each wizard $ i $ will want to visit the house that is exactly $ a_{i} $ $ (0 \leq a_{i} \leq n) $ away from their own house. The roads in the village are built horizontally and vertically, so the distance between points $ (x_{i}, y_{i}) $ and $ (x_{j}, y_{j}) $ on the $ n\times n $ field is $  |x_{i} - x_{j}| + |y_{i} - y_{j}| $ . The wizards know and trust each other, so one wizard can visit another wizard's house when the second wizard is away. The houses to be built will be big enough for all $ n $ wizards to simultaneously visit any house.

Apart from that, each wizard is mandated to have a view of the Hogwarts Castle in the north and the Forbidden Forest in the south, so the house of no other wizard should block the view. In terms of the village, it means that in each column of the $ n\times n $ field, there can be at most one house, i.e. if the $ i $ -th house has coordinates $ (x_{i}, y_{i}) $ , then $ x_{i} \neq x_{j} $ for all $ i \neq j $ .

The Order of the Phoenix doesn't yet know if it is possible to place $ n $ houses in such a way that will satisfy the visit and view requirements of all $ n $ wizards, so they are asking for your help in designing such a plan.

If it is possible to have a correct placement, where for the $ i $ -th wizard there is a house that is $ a_{i} $ away from it and the house of the $ i $ -th wizard is the only house in their column, output YES, the position of houses for each wizard, and to the house of which wizard should each wizard go during the weekends.

If it is impossible to have a correct placement, output NO.

## 说明/提示

For the sample, the house of the 1st wizard is located at $ (4, 4) $ , of the 2nd at $ (1, 3) $ , of the 3rd at $ (2, 4) $ , of the 4th at $ (3, 1) $ .

The distance from the house of the 1st wizard to the house of the 1st wizard is $ |4 - 4| + |4 - 4| = 0 $ .

The distance from the house of the 2nd wizard to the house of the 1st wizard is $ |1 - 4| + |3 - 4| = 4 $ .

The distance from the house of the 3rd wizard to the house of the 1st wizard is $ |2 - 4| + |4 - 4| = 2 $ .

The distance from the house of the 4th wizard to the house of the 3rd wizard is $ |3 - 2| + |1 - 4| = 4 $ .

The view and the distance conditions are satisfied for all houses, so the placement is correct.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1970B1/9f9f415b711c20a1d43262d4b959c18fec467842.png)

## 样例 #1

### 输入

```
4
0 4 2 4```

### 输出

```
YES
4 4
1 3
2 4
3 1
1 1 1 3```

# 题解

## 作者：ikunTLE (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/CF1970B1)

### 构造

![](https://cdn.luogu.com.cn/upload/image_hosting/f9b315hc.png)

如图，鉴于所有的 $a_i$ 都是偶数，若我们将它们全部放置在对角线上，那么它们两两之间的距离为 $2$。

### 计算距离

因为所有的 $a_i$ 全部都在对角线上，只需要在**不出界的前提下**，输出 $a_i\div2$ 并于房屋的编号相加减。

---

## 作者：JOE_ZengYuQiao_0928 (赞：3)

### 先看题：[这是中文版](https://vjudge.net/problem/CodeForces-1970B1#author=GPT_zh)，[这是英文版](https://www.luogu.com.cn/problem/CF1970B1)。
## 思路：
经过推理我们可以得知，因为 $a_i$ 全为偶数，房屋与房屋之间的距离也应是偶数，所以必成功，我们只需要将房屋全建造到对角线上就可以满足条件。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a[200005]; 
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	cout<<"YES\n";
	for(int i=1;i<=n;i++)cout<<i<<" "<<i<<"\n";
	for(int i=1;i<=n;i++){
		if(i-a[i]/2>=1)cout<<i-a[i]/2<<" ";
		else cout<<i+a[i]/2<<" ";
	}
	return 0;
}
```

---

## 作者：Tjl0427 (赞：1)

# 题解：CF1970B1 Exact Neighbours (Easy)
[题目传送门。](https://www.luogu.com.cn/problem/CF1970B1)
### 思路：
推理可得，$a_i$ 是偶数，两房屋的距离也应该是偶数，所以恒成立。只要在对角线上建房就都满足条件。

**注意：数组要开大一点，不能开太小了。**
## 代码：
```c
#include<bits/stdc++.h>//万能头文件
using namespace std;
long long n,a[200005]; 
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){//输入
	    cin>>a[i];
	}
	cout<<"YES\n";//因为一定成立
	for(int i=1;i<=n;i++){
	    cout<<i<<" "<<i<<"\n";
	}
	for(int i=1;i<=n;i++){
		if(i-a[i]/2>=1){
		    cout<<i-a[i]/2<<" ";
		}
		else{
		    cout<<i+a[i]/2<<" ";
		}
	}
	return 0;//养成好习惯
}
```
拜拜！

---

## 作者：JYX0924 (赞：0)

因为房屋距离都是偶数，所以经过推理发现，房屋建造在对角线上是最合理的。每次将距离的一半与房子编号相加减，注意越界情况就可以了。

下面是代码。

```c
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
ll n,a[200005];
int main()
{
	cin>>n; for(ll i=1;i<=n;i++) cin>>a[i];
	cout<<"YES\n";
	for(int i=1;i<=n;i++) cout<<i<<" "<<i<<"\n";
	for(int i=1;i<=n;i++)
	{
		a[i]/=2;
		if(i+a[i]<=n) cout<<i+a[i]<<" ";
		else cout<<i-a[i]<<" ";
	}
	return 0;
}
```
谢谢大家！！！

---

## 作者：zjzx_wcj (赞：0)

# 题解：CF1970B1 Exact Neighbours (Easy)

[题目传送门](/pronlem/CF1970B1)

## 思路

[题目翻译](https://vjudge.net/problem/CodeForces-1970B1#author=GPT_zh)

这是一道构造题。

开始考虑：

![](https://cdn.luogu.com.cn/upload/image_hosting/si16j9f3.png)

我们发现，由于任何 $a_i$ 都是偶数，所以，填在对角线一定是最优的。现在，最主要的问题就是距离的问题。

然后，因为是对角线，所以我们只需要将 $a_i\div2$ 就可以得到对角线的房屋距离，这时我们只需要将其与房屋编号相加或相减就可以得到答案。

## code

```python
n=int (input ())
a=map (int,input ().split ())
a=list (a)
print ('YES')
for i in range (1,n+1):
    print (i,i)
for i in range (1,n+1):
    if i>a[i-1]/2:
        print (i-int (a[i-1]/2),end=' ')
    else:
        print (i+int (a[i-1]/2),end=' ')
```

---

## 作者：Dream_Mr_li (赞：0)

## 思路

限制：$a_i \bmod 2=0$。

![](https://cdn.luogu.com.cn/upload/image_hosting/hjpcllmo.png)

结合题目限制限制和以上图片，我们可以想到，只要把巫师的房子设在对角线上，就可以将此题做对，现在我们遇到的主要问题，就是如何输出符合距离条件的房屋，因为是对角线，所以我们只需要将 $a_i$ 除以二就可以得到对角线的房屋距离，这时我们只需要将其与房屋编号相加或相减就好啦（注意判断是否出界）。


## 代码

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int n,a[N],s;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	cout<<"YES\n";
	for(int i=n;i>=1;i--){
		cout<<i<<" "<<i<<endl;
	}
	for(int i=n;i>=1;i--){
		s=a[i]/2;
		if(i+s<=n){
			cout<<i+s<<" ";
		}else{
			cout<<i-s<<" ";
		}
	}
	return 0;
}
```

---

