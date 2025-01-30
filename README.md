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
