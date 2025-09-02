# Challenging Balloons

## 题目描述

Martha — as a professional problemsetter — proposed a problem for a world-class contest. This is the problem statement:

Tomorrow is Nadia's birthday, and Bardia (her brother) is assigned to make the balloons ready!

There are $ n $ balloons (initially empty) that are tied to a straight line on certain positions $ x_{1},x_{2},...,x_{n} $ . Bardia inflates the balloons from left to right. As a result, $ i $ -th balloon gets bigger and bigger until its radius reaches the pressure endurance $ p_{i} $ or it touches another previously-inflated balloon.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF241G/ad76c1ea81bca8ad7b086e9e6da5329cfb0428b0.png)While Bardia was busy with the balloons, he wondered "What will be the sum of radius of balloons after all of the balloons are inflated?". Being a nerdy type of guy, he is now thinking about the problem instead of preparing his sister's birthday. Calculate the answer to Bardia's problem so that Nadia's birthday won't be balloon-less.

Artha — Martha's student — claimed his solution got accepted. Martha (being his teacher for a long time!) knew he couldn't have solved the problem for real and thus thinks there is something wrong with the testcases. Artha isn't anyhow logical, which means there is no way for Martha to explain the wrong point in his algorithm. So, the only way is to find a testcase to prove him wrong!

Artha's pseudo-code is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF241G/6e961f208c0c9a0d7488024c73cdaa09ded78277.png)You should output a small testcase for the problem such that Artha's algorithm is incorrect. The algorithm's output is considered correct if it differs from the correct value by no more than 1.

## 说明/提示

The testcase depicted in the figure above (just showing how output should be formatted):

`<br></br>4<br></br>0 9<br></br>6 3<br></br>12 7<br></br>17 1<br></br>`

# 题解

## 作者：FFTotoro (赞：1)

CF 远古 hack 题好评。

注意到每次对气球充气时，伪代码仅仅会检查它前面 $300$ 个气球。

所以可以构造出 $302$ 个气球，第一个和最后一个气球半径限度为 $10^6$，位置分别为 $1$ 和 $10^6$；在它们中间合适的位置（可以从大约 $3\times 10^5$ 的位置开始）放 $300$ 个半径限度分别为 $300,299,\ldots,1$ 的气球。

之所以中间的气球半径要递减，是因为伪代码中的循环每次都会清理掉队列中半径比当前气球小的气球（用到了单调队列的思想），这样做可以避免 $300$ 个气球被清掉。

还有一点要注意的是，这 $300$ 个气球中相邻两个的气球的距离一定要足够，以至于气球不会相撞导致半径折损。显然距离为 $300\times 2=600$ 是绝对可以的。

放代码（附 SPJ，供参考）：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
double solve(vector<pii> a,int l){
  double c=0;
  vector<double> r(a.size());
  vector<int> s;
  for(int i=0;i<a.size();i++){
    r[i]=a[i].second;
    for(int j=0;j<min((int)s.size(),l);j++){
      double t=s[s.size()-j-1];
      r[i]=min(r[i],pow(a[i].first-a[t].first,2)/r[t]/4);
    }
    while(!s.empty()&&r[s.back()]<=r[i])s.pop_back();
    s.emplace_back(i),c+=r[i];
  }
  return c;
} // 伪代码中的函数，调换 l 的值可以测试正确和错误的代码
bool spj(vector<pii> a){
  return solve(a,a.size())!=solve(a,300);
}
int main(){
  ios::sync_with_stdio(false);
  vector<pii> a(302);
  a[0]=make_pair(1,1e6);
  for(int i=1;i<=300;i++)
    a[i]=make_pair(3e5+i*600,300-i+1);
  a[301]=make_pair(1e6,1e6);
  if(spj(a)){
    cout<<"302\n";
    for(auto [x,y]:a)
      cout<<x<<' '<<y<<endl;
  }
  else cout<<"Wrong Answer!\n";
  return 0;
}
```

---

