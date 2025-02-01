## 2025년 01월 29일</br>
### 03:01
- MFC Project 기본 UI 세팅</br>
![20250129_DefaultUI](https://github.com/user-attachments/assets/924f4d1e-40cd-4558-8198-0c79d5ae7f53)</br>

## 2025년 01월 30일</br>
### 04:51
- Circle, Curve 등의 Shape를 분리하여 관리할 수 있도록 Shapes 클래스 구현</br>
- Grid Ctrl과 Shapes 간 상호작용 구현</br>
- Shape 클릭 시 주변부 테두리 구현</br>
![20250130_DefaultFramework](https://github.com/user-attachments/assets/c8f9f7e8-b478-436e-a9db-6b2f346c85c2)</br>

### 09:05
- 캐스텔조 알고리즘을 활용한 베지어 곡선 구현</br>
![image](https://github.com/user-attachments/assets/45abc5fe-d8cf-4803-9756-a6d46626f889)</br>
- 위 수식을 구현하기 위해 이항계수와 거듭제곱 계산이 필요하지만, 캐스텔조 방식을 이용하면 단순히 선형 보간을 반복해서 베지어 곡선 구현 가능</br>
1. 1차 보간</br>
![image](https://github.com/user-attachments/assets/5140e93f-755f-4781-8154-d8425e667bca)</br>
2. 2차 보간</br>
![image](https://github.com/user-attachments/assets/5803fc38-05ff-4c27-b3db-ac9411995764)</br>
3. n차 보간</br>
- 계속 반복하여 최종 점 P0(n)(t)를 구하면 베지어 곡선의 점이 된다.</br>
![bandicam2025-01-3009-12-07-397-ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/252f035f-fa7a-4083-963b-4b7e94c338c9)</br>

## 2025년 02월 01일</br>
### 15:20
- CCurve 구조 개선</br>
- Curve는 하나만 존재해도 되는 구조를 반영하여, 기존에 점 생성 시 Curve를 삭제 후 다시 생성하는 로직에서, 기존 Curve를 재정의하는 방식으로 변경</br>
- Redefine 함수를 통해 점을 새로 받아 와서 Curve를 이루는 정점들을 재구성</br>
![image](https://github.com/user-attachments/assets/3fd3a2d5-29fc-4c0e-a9dd-706696ff1846)</br>
- Draw에서 실제로 정점을 이용하여 그려주므로 CCurve::Redefine(...)은 단순히 정점을 받아서 다시 저장하도록 수정 </br>
![image](https://github.com/user-attachments/assets/2a25ae23-611a-4951-a326-c05a841c9724)</br>
- CShapes::Draw(...) 함수에서는 점이 커브에 가리지 않도록 그리는 순서를 변경</br>
![image](https://github.com/user-attachments/assets/904758dc-f84c-4cc2-aeaa-6e2659b7f540)</br>
![ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/61f0fc2e-b672-4e54-8cd6-c98f388a2568)</br>
