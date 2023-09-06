package halsim.socketcan;

import java.io.IOException;
import java.util.concurrent.atomic.AtomicBoolean;

import edu.wpi.first.util.RuntimeLoader;

/**
 * Binds the HAL CAN calls to a SocketCAN device when in simulation
 * 
 * Example usage:
 * <pre>
 * // Say in ip link we have can0
 * </pre>
 */
public class HALSIM_SocketCAN {
  static boolean libraryLoaded = false;
  static RuntimeLoader<HALSIM_SocketCAN> loader = null;

  static class Helper {
    private static AtomicBoolean extractOnStaticLoad = new AtomicBoolean(true);

    public static boolean getExtractOnStaticLoad() {
      return extractOnStaticLoad.get();
    }

    public static void setExtractOnStaticLoad(boolean load) {
      extractOnStaticLoad.set(load);
    }
  }

  static {
    if (Helper.getExtractOnStaticLoad()) {
      try {
        loader = new RuntimeLoader<>("HALSIM_SocketCAN", RuntimeLoader.getDefaultExtractionRoot(), HALSIM_SocketCAN.class);
        loader.loadLibrary();
      } catch (IOException ex) {
        ex.printStackTrace();
        System.exit(1);
      }
      libraryLoaded = true;
    }
  }

  /**
   * Force load the library.
   * @throws java.io.IOException thrown if the native library cannot be found
   */
  public static synchronized void forceLoad() throws IOException {
    if (libraryLoaded) {
      return;
    }
    loader = new RuntimeLoader<>("HALSIM_SocketCAN", RuntimeLoader.getDefaultExtractionRoot(), HALSIM_SocketCAN.class);
    loader.loadLibrary();
    libraryLoaded = true;
  }

  /**
   * Binds the WPILib HAL CAN sim system to the specified SocketCAN interface.
   * @param port The socketcan interface to bind to
   * @return non-negative handle index on success, -1 on failure
   */
  public static native int enable(String port);

  /**
   * Unbinds the WPILib HAL CAN sim system.
   * @param handle the handle from {@link #enable(String port)}
   */
  public static native void clean(int handle);
}
