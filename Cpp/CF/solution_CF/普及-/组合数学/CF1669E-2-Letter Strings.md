# 2-Letter Strings

## 题目描述

你被给予了$n$个长度为2的字符串，每个含有从$a$到$k$的小写字母。找出所有对$(i,j)$使得$i<j$并且第$i$个字符串和第$j$个字符串**刚好**有1个字符不同。

换句话来说，找到所有的数字对$(i,j)(i<j)$使得第$i$个字符串与第$j$个字符串有唯一一个数字$p(1 \leq p \leq 2)$使得$s_{i_p}\neq s_{j_p}$

答案可能超出32位数的范围，所以你在使用c++时应该使用long long等64位变量类型来存储数据避免溢出

注：本题有多数据

## 说明/提示

对于第一个测试样例，符合的字符串对为： ("ab", "cb"), ("ab", "db"), ("ab", "aa"), ("cb", "db") 和 ("cb", "cc")。

对于第二个测试样例，符合的字符串对为： ("aa", "ac"), ("aa", "ca"), ("cc", "ac"), ("cc", "ca"), ("ac", "aa") 和 ("ca", "aa")。

对于最后一个测试样例，没有一种情况符合

## 样例 #1

### 输入

```
4
6
ab
cb
db
aa
cc
ef
7
aa
bb
cc
ac
ca
bb
aa
4
kk
kk
ab
ab
5
jf
jf
jk
jk
jk```

### 输出

```
5
6
0
6```

# 题解

## 作者：Phartial (赞：9)

对于每个字符串，我们其实就是在求某一位相等，而另一位不相等的字符串个数。

不难发现第一位相等和第二位相等两种情况不会有重复，直接枚举不相等的那位是什么字符，累加答案即可。

注意题目中不关心顺序，所以最后求出来答案后还要除以 $2$。

```cpp
#include <iostream>

using namespace std;
using LL = long long;

const int kN = 1e5 + 1;

int t, n, c[11][11], a[kN][2];
LL s;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> t;
  while (t--) {
    cin >> n;
    fill(&c[0][0], &c[10][10] + 1, s = 0);
    for (int i = 1; i <= n; ++i) {
      char x, y;
      cin >> x >> y;
      a[i][0] = x - 'a', a[i][1] = y - 'a';
      ++c[a[i][0]][a[i][1]];  // 累加出现次数
    }
    for (int i = 1; i <= n; ++i) {
      for (int j = 0; j <= 10; ++j) {  // 枚举不同位
        if (j != a[i][0]) {
          s += c[j][a[i][1]];  // 第一位不同，第二位相同的情况
        }
        if (j != a[i][1]) {
          s += c[a[i][0]][j];  // 第一位相同，第二位不同的情况
        }
      }
    }
    cout << s / 2 << endl;
  }
  return 0;
}
```

---

