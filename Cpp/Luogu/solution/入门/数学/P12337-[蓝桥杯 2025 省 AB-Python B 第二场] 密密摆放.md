# [蓝桥杯 2025 省 AB/Python B 第二场] 密密摆放

## 题目描述

小蓝有一个大箱子，内部的长宽高分别是 $200$、$250$、$240$（单位：毫米），他要用这个大箱子来放一些同样大小的小盒子，小盒子的外部长宽高分别是 $30$、$40$、$50$（单位：毫米）。小盒子允许从各个方向旋转（包括可以平放和倒放）。

请问小蓝最多可以在一个大箱子里面放多少个小盒子。

# 题解

## 作者：_luogu_huowenshuo_ (赞：4)

### 计算过程：
小盒子可以以不同的方式旋转，我们有 $6$ 种可能的排列方式。对于每种旋转方式，我们计算每个方向上能够放入多少个小盒子，结果如下：

1. **方式一：** $30 \times 40 \times 50$
   $$
   \left( \frac{L}{a} \right) \times \left( \frac{W}{b} \right) \times \left( \frac{H}{c} \right) = \left( \frac{200}{30} \right) \times \left( \frac{250}{40} \right) \times \left( \frac{240}{50} \right) = 6 \times 6 \times 4 = 144
   $$

2. **方式二：** $30 \times 50 \times 40$
   $$
   \left( \frac{L}{a} \right) \times \left( \frac{W}{c} \right) \times \left( \frac{H}{b} \right) = \left( \frac{200}{30} \right) \times \left( \frac{250}{50} \right) \times \left( \frac{240}{40} \right) = 6 \times 5 \times 6 = 180
   $$

3. **方式三：** $40 \times 30 \times 50$
  $$
   \left( \frac{L}{b} \right) \times \left( \frac{W}{a} \right) \times \left( \frac{H}{c} \right) = \left( \frac{200}{40} \right) \times \left( \frac{250}{30} \right) \times \left( \frac{240}{50} \right) = 5 \times 8 \times 4 = 160
   $$

4. **方式四** $40 \times 50 \times 30$
   $$
   \left( \frac{L}{b} \right) \times \left( \frac{W}{c} \right) \times \left( \frac{H}{a} \right) = \left( \frac{200}{40} \right) \times \left( \frac{250}{50} \right) \times \left( \frac{240}{30} \right) = 5 \times 5 \times 8 = 200
   $$

5. **方式五：** $50 \times 30 \times 40$
   $$
   \left( \frac{L}{c} \right) \times \left( \frac{W}{a} \right) \times \left( \frac{H}{b} \right) = \left( \frac{200}{50} \right) \times \left( \frac{250}{30} \right) \times \left( \frac{240}{40} \right) = 4 \times 8 \times 6 = 192
   $$

6. **方式六：** $50 \times 40 \times 30$
   $$
   \left( \frac{L}{c} \right) \times \left( \frac{W}{b} \right) \times \left( \frac{H}{a} \right) = \left( \frac{200}{50} \right) \times \left( \frac{250}{40} \right) \times \left( \frac{240}{30} \right) = 4 \times 6 \times 8 = 192
   $$

## 答案
最大数量是 $200$，因此小蓝最多可以放入 $200$ 个小盒子。

---

## 作者：AFO_Lzx (赞：4)

设大箱子的体积为 $V_1$，小箱子的体积为 $V_2$，则根据体积公式可得：可以放下 $\dfrac{V_1}{V_2}=\dfrac{200 \times 250 \times 240}{30 \times 40 \times 50} = 200$ 个小箱子，代码特别简单，输出 $200$ 即可。

```cpp
#include<bits/stdc++.h>
using ll = long long;
using namespace std;

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cout << 200 << '\n';
	return 0;
}
```

---

## 作者：Clare613 (赞：2)

## 思路
用大盒子的体积除以小盒子的体积即可，因为 $240$ 是 $30$ 的倍数，$200$ 是 $40$ 的倍数，$250$ 是 $50$ 的倍数，有的题解没提到这点，这里给予补充。
```cpp
#include<bits/stdc++.h>
using namespace std;

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	cout<<(200*250*240)/(30*40*50);
	return 0;
}
```

---

## 作者：HP_Serenity (赞：1)

通过读题可以发现能够放入最多小盒子的旋转方式为 $40 \times 50 \times 30$，那么沿大箱子长可以放入 $200 \div 40 = 5$ 个小盒子，沿大箱子宽可以放入 $250 \div 50 = 5$ 个小盒子，沿大箱子高可以放入 $240 \div 30 = 8$ 个小盒子。所以答案就是 $5 \times 5 \times 8 = 200$ 个小盒子。

---

## 作者：zhoujunchen (赞：0)

数学题。

大箱子的长可以放 $200\div40=5$ 个，宽可以放 $250\div 50=5$ 个，高可以放 $240\div30=8$ 个，总共可以放 $5\times5\times8=200$ 个。

---

## 作者：封禁用户 (赞：0)

## 题目大意
[题目传送门](https://www.luogu.com.cn/problem/P12337)
## 题目分析
希望审核大大给过。

这是一道公式计算题，我们都知道，长方形的体积为 $V = a \times b \times h$，大小长方形都如此。因此可以套用公式。

代码如下：
## 题目代码
C++ 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cout<<200/40*250/50*240/30;
	return 0;
}
```
python 代码：
```python
print(200//40*250//50*240//30)
```

---

## 作者：CCY20130127 (赞：0)

## 题目大意：
[密密摆放](https://www.luogu.com.cn/problem/P12337)

上方是题目传送门。

## 题目分析：
这道题用小学的知识就可以过。总所周知，长方体的体积公式为：
$$V=a \times b \times h$$
那么求出大箱子和小盒子相除就行了。

## 正解：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cout<<(200*250*240)/(30*40*50);
	return 0;
}
```

---

## 作者：wangyanxiang2013 (赞：0)

根据公式 $V=a \times b \times h$ 算出箱子和小盒子的体积，相除即可。

上代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	cout<<(200*250*240)/(30*40*50);
	return 0;
}
```

---

