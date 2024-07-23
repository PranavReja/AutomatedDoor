import cv2
import time
import os  # Added for saving images
import subprocess



face_classifier = cv2.CascadeClassifier(
    cv2.data.haarcascades + "haarcascade_frontalface_default.xml"
)

video_capture = cv2.VideoCapture(0)

def detect_bounding_box(vid):
    gray_image = cv2.cvtColor(vid, cv2.COLOR_BGR2GRAY)
    faces = face_classifier.detectMultiScale(gray_image, 1.1, 5, minSize=(40, 40))
    return faces, gray_image  # Return both faces and grayscale image

    
start_time = None
face_tracked_duration = 0
image_count = 0  # Initialize image counter for unique filenames



subprocess.Popen("python3 app.py",text=True, shell = True)
while True:

    result, video_frame = video_capture.read()  # Read frames from the video
    if result is False:
        break  # Terminate the loop if the frame is not read successfully

    faces, gray_image = detect_bounding_box(video_frame)  # Apply detection

    # Track face detection duration
    if len(faces) > 0:  # If a face is detected
        if start_time is None:
            start_time = time.time()
        current_time = time.time()
        face_tracked_duration = current_time - start_time
    else:  # If no face is detected, reset the timer and duration
        start_time = None
        face_tracked_duration = 0

    # Take picture if face is detected for at least 3 seconds
    if 1.7 >= face_tracked_duration >= 1.5:
        filename = "captured_image.jpg"
        path = '/home/pranav/webapp/static'
        cv2.imwrite(os.path.join(path , filename), video_frame)
        subprocess.Popen("python3 client.py",text=True, shell = True)

        

    # Draw bounding box and display tracking duration (optional)
    for (x, y, w, h) in faces:
        cv2.rectangle(video_frame, (x, y), (x + w, y + h), (0, 255, 0), 4)
        # Optionally display tracking duration on the frame:
        tracking_duration_text = f"Face Tracked: {face_tracked_duration:.2f} seconds"
        cv2.putText(video_frame, tracking_duration_text, (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 0), 2)

    cv2.imshow("My Face Detection Project", video_frame)  # Display the processed frame
    



    if cv2.waitKey(1) & 0xFF == ord("q"):
        break

video_capture.release()
cv2.destroyAllWindows()

