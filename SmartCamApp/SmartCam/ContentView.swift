//
//  ContentView.swift
//  SmartCam
//
//  Created by Jasson Rodríguez Méndez on 15/6/21.
//

import SwiftUI
import AVKit

struct ContentView: View {
    var body: some View {
        let livestream = AVPlayer(url: URL(string: "http://192.168.100.54:8000/playlist.m3u8")!)
        VideoPlayer(player: livestream)
            .frame(height: 400)
            .onAppear() {
                livestream.play()
            }
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
