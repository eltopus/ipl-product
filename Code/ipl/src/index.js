const { app, BrowserWindow, Notification, ipcMain } = require('electron')
const path = require('path');
let myWindow;

// Handle creating/removing shortcuts on Windows when installing/uninstalling.
if (require('electron-squirrel-startup')) {
  app.quit();
}

const NOTIFICATION_TITLE = 'Welcome';
const NOTIFICATION_BODY = 'WQelcome to IPL v5.0.0';

function showNotification() {
  new Notification({title: NOTIFICATION_TITLE, body: NOTIFICATION_BODY}).show();
}


function showCustomNotification(options) {
  options["icon"] = path.join(__dirname, 'images/icon.png');
  new Notification(options).show();
}

const createWindow = () => {
  // Create the browser window.
  const mainWindow = new BrowserWindow({
    width: 1024,
    height: 800,
    webPreferences: {
      preload: path.join(__dirname, 'preload.js'),
    },
    icon: 'images/icon.png',
  });

  // and load the index.html of the app.
  mainWindow.loadFile(path.join(__dirname, 'index.html'));
  
  // Open the DevTools.
  //mainWindow.webContents.openDevTools();

  ipcMain.handle('openDevTools', () => {
    console.log("i got here from the inside......");
    mainWindow.webContents.openDevTools();
    showNotification();
  });

  ipcMain.handle('showCustomNotification', (event, options) => {
    console.log("Attempting to show custom notification.....");
    //console.log(options);
    showCustomNotification(options);
  });
  
};



// This method will be called when Electron has finished
// initialization and is ready to create browser windows.
// Some APIs can only be used after this event occurs.
app.on('ready', createWindow);

// Quit when all windows are closed, except on macOS. There, it's common
// for applications and their menu bar to stay active until the user quits
// explicitly with Cmd + Q.
app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') {
    app.quit();
  }
});

app.on('activate', () => {
  // On OS X it's common to re-create a window in the app when the
  // dock icon is clicked and there are no other windows open.
  if (BrowserWindow.getAllWindows().length === 0) {
    createWindow();
  }
});

// In this file you can include the rest of your app's specific main process
// code. You can also put them in separate files and import them here.


