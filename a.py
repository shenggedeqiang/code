import cv2
import mediapipe as mp

# 初始化 MediaPipe Pose 模块
mp_pose = mp.solutions.pose
pose = mp_pose.Pose(min_detection_confidence=0.5, min_tracking_confidence=0.5)

# 初始化 MediaPipe 绘图模块
mp_drawing = mp.solutions.drawing_utils

# 打开视频
cap = cv2.VideoCapture('input_video.mp4')  # 替换为你的输入视频文件路径

while cap.isOpened():
    ret, frame = cap.read()
    if not ret:
        break

    # 将 BGR 图像转换为 RGB 图像
    rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

    # 进行姿态估计
    results = pose.process(rgb_frame)

    # 绘制结果
    if results.pose_landmarks:
        # 在图像上绘制关节点和骨架
        mp_drawing.draw_landmarks(frame, results.pose_landmarks, mp_pose.POSE_CONNECTIONS)

    # 显示结果图像
    cv2.imshow('Pose Estimation', frame)

    # 按键 'q' 退出
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# 释放视频资源
cap.release()
cv2.destroyAllWindows()

==================================
如果你想处理实时视频（例如摄像头输入），只需要将 cv2.VideoCapture 改为摄像头设备的索引：

cap = cv2.VideoCapture(0)  # 使用摄像头（0是默认摄像头）

===============================
将每一帧图像预测的关键点数据保存为json文件
import cv2
import mediapipe as mp
import json

# 初始化 MediaPipe Pose 模块
mp_pose = mp.solutions.pose
pose = mp_pose.Pose(min_detection_confidence=0.5, min_tracking_confidence=0.5)

# 打开视频
cap = cv2.VideoCapture('input_video.mp4')  # 替换为你的输入视频文件路径

# 用于存储每帧的关键点数据
frame_data = []

frame_id = 0
while cap.isOpened():
    ret, frame = cap.read()
    if not ret:
        break

    # 将 BGR 图像转换为 RGB 图像
    rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

    # 进行姿态估计
    results = pose.process(rgb_frame)

    if results.pose_landmarks:
        landmarks = []
        # 将每一帧的关键点保存到字典中
        for landmark_id, landmark in enumerate(results.pose_landmarks.landmark):
            landmarks.append({
                "landmark_id": landmark_id,
                "x": landmark.x,
                "y": landmark.y,
                "z": landmark.z,
                "visibility": landmark.visibility
            })
        frame_data.append({"frame": frame_id, "landmarks": landmarks})

    frame_id += 1

# 将所有帧的数据写入到 JSON 文件
with open('pose_landmarks.json', 'w') as json_file:
    json.dump(frame_data, json_file, indent=4)

# 释放视频资源
cap.release()
cv2.destroyAllWindows()

