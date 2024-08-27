
# TimeStretcher

![TimeStretcher Logo](./assets/logo.png)

## Overview

**TimeStretcher** is a C++ application designed for batch time-stretching WAV files. It allows users to process audio files by stretching them to different BPMs, making it ideal for musicians, DJs, and sound designers who need to manipulate the tempo of their audio samples without affecting pitch.

## Features

- **Batch Processing**: Process an entire folder of WAV files in one go.
- **Custom Output Folder**: Specify an output directory with the `-o` flag or default to creating subdirectories within the input folder.
- **Multiple BPMs**: Stretch audio files to multiple BPMs in a single run.
- **Cross-Platform**: Works on Linux and other platforms that support C++17 and the required libraries.

## Usage

### Command Line

```bash
./TimeStretcher <input_folder> <bpm_list> [-o <output_folder>]
```

- `<input_folder>`: Path to the folder containing the WAV files you want to process.
- `<bpm_list>`: A comma-separated list of BPM values to stretch the files to.
- `-o <output_folder>`: (Optional) Specify a custom output folder. If not provided, the application will create subdirectories in the input folder named after each BPM.

### Examples

**Default Output Folder:**

```bash
./TimeStretcher /home/user/audio "120,160"
```

This command will process all WAV files in the `/home/user/audio` directory, creating subdirectories for each BPM (e.g., `/home/user/audio/120/`, `/home/user/audio/160/`) with the processed files.

**Custom Output Folder:**

```bash
./TimeStretcher /home/user/audio "120,160" -o /home/user/output
```

This command will save the processed files in the specified output folder `/home/user/output/`.

## Dependencies

- **SoundTouch**: Library for time-stretching audio.
- **libsndfile**: Library for reading and writing WAV files.
- **C++17**: The application requires a C++17 compatible compiler.

## Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/yourusername/TimeStretcher.git
   cd TimeStretcher
   ```

2. Install dependencies:

   On Debian/Ubuntu:

   ```bash
   sudo apt-get install libsoundtouch-dev libsndfile-dev
   ```

3. Build the application using Meson:

   ```bash
   meson setup builddir
   meson compile -C builddir
   ```

4. Run the application:

   ```bash
   ./builddir/timestretcher /path/to/input_folder "120,160"
   ```

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Contributing

Contributions are welcome! Please fork this repository, make your changes, and submit a pull request.

---

Thank you for using **TimeStretcher**! If you have any questions or issues, feel free to open an issue in the repository.
