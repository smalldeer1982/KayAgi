# Death Stars (medium)

## 题目描述

The stardate is 1983, and Princess Heidi is getting better at detecting the Death Stars. This time, two Rebel spies have yet again given Heidi two maps with the possible locations of the Death Star. Since she got rid of all double agents last time, she knows that both maps are correct, and indeed show the map of the solar system that contains the Death Star. However, this time the Empire has hidden the Death Star very well, and Heidi needs to find a place that appears on both maps in order to detect the Death Star.

The first map is an $ N×M $ grid, each cell of which shows some type of cosmic object that is present in the corresponding quadrant of space. The second map is an $ M×N $ grid. Heidi needs to align those two maps in such a way that they overlap over some $ M×M $ section in which all cosmic objects are identical. Help Heidi by identifying where such an $ M×M $ section lies within both maps.

## 说明/提示

The 5-by-5 grid for the first test case looks like this:

```
<pre class="verbatim"><br></br>mayth<br></br>eforc<br></br>ebewi<br></br>thyou<br></br>hctwo<br></br>
```

## 样例 #1

### 输入

```
10 5
somer
andom
noise
mayth
eforc
ebewi
thyou
hctwo
again
noise
somermayth
andomeforc
noiseebewi
againthyou
noisehctwo
```

### 输出

```
4 6
```

# 题解

## 作者：FFTotoro (赞：1)

字符串哈希板子题。考虑如何将 $A$ 的一个 $m\times m$ 的子矩阵匹配到 $B$ 中一个完全相等的，想到哈希，对于 $A$ 中所有子矩阵进行编码，用一个 `std::map` 存储，对于 $B$ 的每一个子矩阵在 `map` 中扫一遍，如果它的哈希值出现过就直接输出答案。

这里用的单模哈希，选的模数为 $10^9+9$，Base（进制数）为 $6803$，足以通过。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+9,base=6803;
map<int,int> p;
main(){
  ios::sync_with_stdio(false);
  int n,m; cin>>n>>m;
  vector<string> a(n),b(m);
  for(auto &i:a)cin>>i;
  for(auto &i:b)cin>>i;
  for(int i=0;i<=n-m;i++){
    int c=0;
    for(int j=i;j<i+m;j++)
      for(char k:a[j])c=(c*base+k-96)%mod;
    p[c]=i+1; // 将哈希值存入 map
  }
  for(int i=0;i<=n-m;i++){
    int c=0;
    for(int j=0;j<m;j++)
      for(int k=i;k<i+m;k++)
        c=(c*base+b[j][k]-96)%mod;
    if(p[c]){ // 该值存在
      cout<<p[c]<<' '<<i+1<<endl; break;
    }
  }
  return 0;
}
```

---

## 作者：1234567890sjx (赞：0)

考虑把 $a$、$b$ 两个数组都写一个 2-D 哈希，然后发现行、列都很少，所以枚举 $a$ 数组的起始行、$b$ 数组的起始列，计算出这两个子矩阵的 2-D 哈希值，判断其是否相等。如果其相等那么就计算出了一组合法的解，否则继续枚举即可。

时间复杂度为 $O(nm)$。十分好写。

---

