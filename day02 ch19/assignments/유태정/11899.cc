#include <iostream>
#include <stack>

using namespace std;

int main() {
  // g++로 컴파일할 때, -D_DEBUG 옵션을 주면 아래처럼 쓸 수 있답니다.
#ifdef _DEBUG
  freopen("input.txt", "r", stdin);
#endif

  // 한 줄을 통째로 입력 받습니다.
  string input;
  cin >> input;

  // 괄호열을 저장할 스택입니다.
  stack<char> parenthesis_array;

  // 입력 받은 괄호열에서 하나 씩 꺼내봅니다.
  for (auto& parenthesis : input) {
    // 막 가져온 괄호랑 스택의 top의 괄호가 쌍을 이루면 pop을 합니다.
    // 짝이 이미 맞춰졌으니 신경 쓸 필요가 없기 때문입니다!
    if (parenthesis_array.size() && parenthesis_array.top() - parenthesis == -1) {
      parenthesis_array.pop();
    } else {
      // 그렇지 않으면 스택에 넣어둡니다.
      parenthesis_array.push(parenthesis);
    }
  }

  // 그렇게 이미 짝이 맞는 괄호들을 제외하면 짝이 맞지 않는 애들만 남습니다.
  // 이들의 짝을 모두 지어주면 되니까, 그 수가 곧 답입니다.
  cout << parenthesis_array.size() << endl;

  return 0;
}