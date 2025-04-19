import RPi.GPIO as GPIO
import subprocess
import time

# === Motor Setup ===
DIR_PIN = 5
STEP_PIN = 6
STEP_DELAY = 0.001
STEPS_PER_MOVE = 320  # 30° per move (180° sweep = 1600 total steps)

# === Camera Multiplexer ===
I2C_BUS = 10
I2C_ADDR = "0x24"
I2C_REG = "0x24"
CHANNEL_VALUES = ["0x02", "0x12", "0x22", "0x32"]  # Channels for 4 cameras

# === GPIO Setup ===
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(DIR_PIN, GPIO.OUT)
GPIO.setup(STEP_PIN, GPIO.OUT)
GPIO.output(DIR_PIN, GPIO.HIGH)  # Use LOW to reverse direction if needed


# === Motor Control ===
def rotate_motor(steps):
    print(f"[MOTOR] Rotating {steps} steps...")
    for _ in range(steps):
        GPIO.output(STEP_PIN, GPIO.HIGH)
        time.sleep(STEP_DELAY)
        GPIO.output(STEP_PIN, GPIO.LOW)
        time.sleep(STEP_DELAY)


# === Camera Functions ===
def switch_camera(cam_index):
    value = CHANNEL_VALUES[cam_index]
    print(f"[INFO] Switching to camera {cam_index} (I2C: {value})")
    subprocess.run(["i2cset", "-y", str(I2C_BUS), I2C_ADDR, I2C_REG, value])
    time.sleep(2.0)  # Allow sensor to stabilize before capture


def capture_camera(cam_index, frame_index):
    filename = f"frame{frame_index}_cam{cam_index}.jpg"
    print(f"[INFO] Capturing {filename}")
    cmd = [
        "libcamera-still",
        "-n",
        "--timeout",
        "2000",
        "--denoise",
        "off",
        "--width",
        "4624",
        "--height",
        "3472",
        "-q",
        "100",
        "-o",
        filename,
    ]
    result = subprocess.run(cmd, capture_output=True)
    if result.returncode != 0:
        print(f"[ERROR] Capture failed: {result.stderr.decode().strip()}")


# === Main Sequence ===
def main():
    print("📸 Starting photogrammetry sequence...")
    num_positions = 6  # 0°, 30°, ..., 150°
    try:
        for i in range(num_positions):
            print(f"\n=== Position {i+1}/{num_positions} ===")
            for cam in range(4):
                switch_camera(cam)
                capture_camera(cam, i)
            if i < num_positions - 1:
                rotate_motor(STEPS_PER_MOVE)
    finally:
        GPIO.cleanup()
        print("✅ Done. GPIO cleaned up.")


if __name__ == "__main__":
    main()
