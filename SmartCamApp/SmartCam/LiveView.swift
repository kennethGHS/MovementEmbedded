//
//  LiveView.swift
//  SmartCam
//
//  Created by Jasson Rodríguez Méndez on 18/6/21.
//

import SwiftUI
import AVKit

struct LiveView: View {
    let livestream = AVPlayer(url: URL(string: "http://192.168.100.62/stream.m3u8")!)
    var body: some View {
        VideoPlayer(player: livestream)
            .frame(height: 300)
            .onAppear() {
                livestream.play()
            }
    }
}

struct LiveView_Previews: PreviewProvider {
    static var previews: some View {
        LiveView()
    }
}
