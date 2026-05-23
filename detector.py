import cv2
from ultralytics import YOLO
model = YOLO("yolov8n.pt")  
PETS = {
   15: "Gato",
   16: "Cachorro",
   17: "Cavalo",
   18: "Ovelha"
}

cap = cv2.VideoCapture(0)
print("Sistema iniciado! Pressione Q para sair.")
while True:
   ret, frame = cap.read()
   if not ret:
       break
   results = model(frame, verbose=False)
   pet_detectado = False
   for result in results:
       for box in result.boxes:
           cls_id = int(box.cls[0])
           confianca = float(box.conf[0])
           if cls_id in PETS and confianca > 0.5:
               pet_detectado = True
               label = f"{PETS[cls_id]} {confianca:.0%}"
               x1, y1, x2, y2 = map(int, box.xyxy[0])
               cv2.rectangle(frame, (x1, y1), (x2, y2), (0, 255, 0), 2)
               cv2.putText(frame, label, (x1, y1 - 10),
                   cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 255, 0), 2)
   if pet_detectado:
       cv2.putText(frame, "PET DETECTADO!",
           (20, 50), cv2.FONT_HERSHEY_SIMPLEX,
           1.2, (0, 0, 255), 3)
   cv2.imshow("Pet Detector - FIAP", frame)
   if cv2.waitKey(1) & 0xFF == ord('q'):
       break
cap.release()
cv2.destroyAllWindows()